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

GdtTableEntry gdt[GDT_ENTRIES];
GdtTablePtr gdt_ptr;

void KiSetGdtTableEntry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[num].base_low = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = limit & 0xFFFF;
    gdt[num].granularity = (limit >> 16) & 0x0F;
    gdt[num].granularity |= granularity & 0xF0;
    gdt[num].access = access;
}

void KiSetGdtTablePtr() {
    gdt_ptr.limit = (sizeof(GdtTableEntry) * GDT_ENTRIES) - 1;
    gdt_ptr.base = (uint32_t)&gdt;
}

void KiInitGdt() {
    KiSetGdtTableEntry(0, 0, 0, 0, 0);  
    KiSetGdtTableEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 
    KiSetGdtTableEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    KiSetGdtTableEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    KiSetGdtTableEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); 

    KiSetGdtTablePtr();
    KiFlushGdtTable((uint32_t)&gdt_ptr);
}