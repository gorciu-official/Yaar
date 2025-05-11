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

#pragma once

#include <types.h>

#define IDT_ENTRIES 256

typedef struct {
    uint16_t offset_low;
    uint16_t selector; 
    uint8_t zero; 
    uint8_t type_attr;
    uint16_t offset_high; 
} __attribute__((packed)) IdtTableEntry;

typedef struct {
    uint16_t limit;
    uint32_t base; 
} __attribute__((packed)) IdtTablePtr;