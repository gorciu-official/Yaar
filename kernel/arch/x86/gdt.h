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

#define GDT_ENTRIES 5

typedef struct {
    uint16_t limit_low; 
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access; 
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) GdtTableEntry;

typedef struct {
    uint16_t limit; 
    uint32_t base; 
} __attribute__((packed)) GdtTablePtr;

extern void KiFlushGdtTable(uint32_t);