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

OSENTRY void KiBootOS() {
    SystemArchitecture arch = KiDetectArchitecture();

    if (arch == UnknownArchitecture) {
        // This can lead to undefined/unexpected behavior, so
        // we have no other option or to just return from the function.
        // No harm done since there is an compiler warning in the same
        // file as KiDetectArchitecture implementation.
        return;
    }

    bool arch_x86_like = arch == x32 || arch == x64;
    bool arch_long_mode_capable = arch == x64;

    return;
}