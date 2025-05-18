#include <types.h>
#include "ps2.h"
#include <drivers/screen.h>

static volatile uint8_t kbd_buffer[KBD_BUFFER_SIZE];
static volatile uint16_t kbd_head = 0;
static volatile uint16_t kbd_tail = 0;

static void pic_send_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(0xA0, PIC_EOI); 
    }
    outb(0x20, PIC_EOI); 
}

static void kbd_buffer_put(uint8_t scancode) {
    uint16_t next = (kbd_head + 1) % KBD_BUFFER_SIZE;
    if (next != kbd_tail) { // sprawdź czy nie jest pełny
        kbd_buffer[kbd_head] = scancode;
        kbd_head = next;
    }
}

static bool kbd_buffer_available() {
    return kbd_head != kbd_tail;
}

static uint8_t kbd_buffer_get() {
    if (kbd_head == kbd_tail) return 0;
    uint8_t val = kbd_buffer[kbd_tail];
    kbd_tail = (kbd_tail + 1) % KBD_BUFFER_SIZE;
    return val;
}

void ps2_handler_main(void* frame) {
    uint8_t scancode = inb(PS2_DATA_PORT);
    kbd_buffer_put(scancode);
    pic_send_eoi(1);
}

static char scancode_to_ascii(uint8_t scancode) {
    static const char lookup[128] = {
        0,   27, '1', '2', '3', '4', '5', '6', 
        '7', '8', '9', '0', '-', '=', '\b', '\t',
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
        'o', 'p', '[', ']', '\n', 0,  'a', 's',
        'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 
        '\'', '`', 0,  '\\', 'z', 'x', 'c', 'v',
        'b', 'n', 'm', ',', '.', '/', 0,   '*', 
        0,   ' ', 0,    0,   0,   0,   0,   0,
    };
    if (scancode < 128)
        return lookup[scancode];
    return 0;
}

uint32_t ps2_read(char* out_buf, uint32_t max_length, bool secret, int color) {
    uint32_t read_count = 0;

    if (max_length == 0)
        return 0;

    while (kbd_buffer_available() && read_count < max_length - 1) {
        uint8_t code = kbd_buffer_get();
        char ch = scancode_to_ascii(code);

        if (ch) {
            out_buf[read_count++] = ch;

            if (!secret) {
                putchar(ch, color);
            }
        }
    }

    out_buf[read_count] = '\0';
    return read_count;
}