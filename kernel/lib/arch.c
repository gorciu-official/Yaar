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
#include <architectures.h>

SystemArchitecture KiDetectArchitecture() {
    #ifdef __x86_64__
        return x64;
    #endif

    #ifdef __i386__
        return x32;
    #endif

    #ifdef __aarch64__
        return AArch64;
    #endif

    #ifdef __asm__
        return ARM;
    #endif

    return UnknownArchitecture;
}

#if !defined(__asm__) && !defined(__aarch64__) && !defined(__x86_64__) && !defined(__i386__)
#warning AurorOS will bootloop because of a undefined behavior on the target architecture.
#warning Currently supported architectures are: ASM (32-bit/64-bit), x86 and x86_64
#endif