/*
 * ===========================================================================
 *
 *       Filename:  dbg_flash.h
 *
 *    Description:  Debug flash
 *
 *        Version:  1.0
 *        Created:  09/09/2012 12:14:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  3VSoft
 *
 * ===========================================================================
 */
#if !defined (__DBG_FLASH_H__)
#define __DBG_FLASH_H__

#include <util/delay.h>

#if !defined (SBI)
#define SBI(p, b) ((p) |= 1 << (b))
#endif

#if !defined (CBI)
#define CBI(p, b) ((p) &= ~(1 << (b)))
#endif

#define DBG_FLASH(DDR, PORT, PIN, N) \
    { \
        uint8_t n = (N); \
        SBI (DDR, PIN); \
        while (n--) \
        { \
            SBI (PORT, PIN); \
            _delay_ms (200); \
            CBI (PORT, PIN); \
            _delay_ms (200); \
        } \
    } \


#endif//__DBG_FLASH_H__
