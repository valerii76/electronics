/*
 * =====================================================================================
 *
 *       Filename:  ds1wire.h
 *
 *    Description:  One wire interface
 *
 *        Version:  1.0
 *        Created:  11/24/2012  8:28:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valery.volgutov@lge.com
 *        Company:  LGE
 *
 * =====================================================================================
 */
#if !defined (__DS1WIRE_H__)
#define __DS1WIRE_H__

#include <inttypes.h>

typedef void (*ds1wire_add_address) (uint8_t const *address);

enum
{
    DS1WIRE_OK = 0,
    DS1WIRE_NO_DEVICES,
    DS1WIRE_LOW,
    DS1WIRE_HIGH,
};

/*
 * One wire interface initialization
 * returns:
 *      DS1WIRE_OK - ok
 *      DS1WIRE_NO_DEVICES - devices does't response
 */
uint8_t ds1wire_start (void);

/*
 * One wire interface sent byte
 * @param:
 *      b - data for send to device
 */
void ds1wire_send_byte (uint8_t b);

/*
 * One wire interface receive byte
 * returns:
 *      byte from device
 */
uint8_t ds1wire_receive_byte (void);

/*
 * One wire interface get line status
 */
uint8_t ds1wire_line_status (void);

/*
 * search ROM for devices
 */
void ds1wire_search_rom (ds1wire_add_address add_func);

#endif//__DS1WIRE_H__
