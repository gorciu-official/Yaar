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
#include "gdt.h"

gdt_entry_t gdt[GDT_ENTRIES];
gdt_ptr_t gdt_ptr;

void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[num].base_low = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = limit & 0xFFFF;
    gdt[num].granularity = (limit >> 16) & 0x0F;
    gdt[num].granularity |= granularity & 0xF0;
    gdt[num].access = access;
}

void set_gdt_ptr() {
    gdt_ptr.limit = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;
    gdt_ptr.base = (uint32_t)&gdt;
}

void init_gdt() {
    set_gdt_entry(0, 0, 0, 0, 0);  
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); 

    set_gdt_ptr();
    flush_gdt((uint32_t)&gdt_ptr);
}

void real_init_gdt() {
    asm volatile("lgdt (%0)" : : "r"(&gdt_ptr));
    return;
}