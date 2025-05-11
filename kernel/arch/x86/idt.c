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
#include "idt.h"

IdtTableEntry idt[IDT_ENTRIES];
IdtTablePtr idt_ptr; 

void KiSetIdtTableEntry(int num, uint32_t base, uint16_t selector, uint8_t type_attr) {
    idt[num].offset_low = base & 0xFFFF;
    idt[num].offset_high = (base >> 16) & 0xFFFF;
    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].type_attr = type_attr;
}

void KiSetIdtTablePtr() {
    idt_ptr.limit = (sizeof(IdtTableEntry) * IDT_ENTRIES) - 1;
    idt_ptr.base = (uint32_t)&idt;
}

void init_idt() {
    KiSetIdtTablePtr();
    KiFlushIdtTable((uint32_t)&idt_ptr);
}