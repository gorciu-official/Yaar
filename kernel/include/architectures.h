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

typedef enum { UnknownArchitecture, x64, x32, ARM, AArch64 } SystemArchitecture;
extern SystemArchitecture KiDetectArchitecture();