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

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}