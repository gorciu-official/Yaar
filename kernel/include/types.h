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

/**
 * just for finding quickly OS entries for specific architectures.
 */
#define OSENTRY

/* numbers types */
typedef signed char		    int8_t;
typedef unsigned char		uint8_t;
typedef short			    int16_t;
typedef unsigned short		uint16_t;
typedef int			        int32_t;
typedef unsigned		    uint32_t;
typedef long long		    int64_t;
typedef unsigned long long	uint64_t;

/* cpp-like types */
#ifndef __cplusplus
typedef enum {false, true} bool; 
// ^ you can NOT align this to 1 bit, it uses 32-bits, do not make shitty comments without understanding the topic
#endif