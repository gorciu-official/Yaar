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
#include <arch/x86.h>

OSENTRY void KiBootOS() {
    SystemArchitecture arch = KiDetectArchitecture();

    if (arch == UnknownArchitecture) {
        // This can lead to undefined/unexpected behavior, so
        // we have no other option or to just return from the function.
        // No harm done since there is an compiler warning in the same
        // file as KiDetectArchitecture implementation.
        return;
    }

    if (arch == x32 || arch == x64) {
        KiInitGdt();
        KiInitIdt();
        KiEnterProtectedMode();
    }

    return;
}

void KiSystemReady() {
    // is OS really ready?
    static int execution_times = 0;
    execution_times++;
    if (KiDetectArchitecture() == x64 && execution_times == 1) {
        // we need to initialize now long mode from protected
        // i will do it later
        return;
    }

    // now it is ready
    return;
}