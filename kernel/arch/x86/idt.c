/**
 * ================================================================
 *                            AurorOS
 * ================================================================
 * 
 * This code is served by the terms specified in the AurorOS 
 * license. If you did not get one, you can get a copy on AurorOS's
 * original repository: https://github.com/Interpuce/AurorOS and
 * then switching the tab from ReadMe to License.
*/

#include <types.h>
#include <ports.h>
#include "idt.h"

extern void irq1_handler(void);

idt_entry_t idt[IDT_ENTRIES];
idt_ptr_t idt_ptr; 

void set_idt_entry(int num, uint32_t base, uint16_t selector, uint8_t type_attr) {
    idt[num].offset_low = base & 0xFFFF;
    idt[num].offset_high = (base >> 16) & 0xFFFF;
    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].type_attr = type_attr;
}

void set_idt_ptr() {
    idt_ptr.limit = (sizeof(idt_entry_t) * IDT_ENTRIES) - 1;
    idt_ptr.base = (uint32_t)&idt;
}

void remap_irq_handlers() {
    uint8_t mask_master = inb(0x21);
    uint8_t mask_slave = inb(0xA1);

    outb(0x20, 0x11);   // start initialization master PIC
    outb(0xA0, 0x11);   // start initialization slave PIC

    outb(0x21, 0x20);   // master PIC offset (0x20)
    outb(0xA1, 0x28);   // slave PIC offset (0x28)

    outb(0x21, 0x04);   // inform master PIC about slave at IRQ2
    outb(0xA1, 0x02);   // inform slave PIC about cascade identity

    outb(0x21, 0x01);   // set 8086/88 mode
    outb(0xA1, 0x01);   // set 8086/88 mode

    // outb(0x21, 0x0);    // unmask all IRQs on master
    // outb(0xA1, 0x0);    // unmask all IRQs on slave
    // ^ i used to have this code but teh code below
    //                               *the
    //  overrides these zeros so no need for that

    outb(0x21, mask_master);
    outb(0xA1, mask_slave);
}

void init_idt() {
    remap_irq_handlers(); // without this the PS/2 interrupt is strange
    set_idt_entry(0x21, (uint16_t)irq1_handler, 0x08, 0x8E);
    set_idt_ptr();
    flush_idt((uint32_t)&idt_ptr);
}