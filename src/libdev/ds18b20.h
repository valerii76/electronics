/*
 * =====================================================================================
 *
 *       Filename:  ds18b20.h
 *
 *    Description:  DS18B20 interface implementation
 *
 *        Version:  1.0
 *        Created:  11/25/2012  3:28:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  3VSoft
 *
 * =====================================================================================
 */
#if !defined (__DS18B20_H__)
#define __DS18B20_H__

#include <inttypes.h>

enum
{
    DS18B20_OK = 0,
    DS18B20_NO_DEVICES,
};

/*
 * search ds18b20 devices
 */
uint8_t ds18b20_search (void);

/*
 * number of ds18b20 devices
 */
uint8_t ds18b20_device_number (void);

/*
 * get address for device
 */
uint8_t const* ds18b20_device_address (uint8_t i);

/*
 * get temperature from device
 */
int16_t ds18b20_temperature (uint8_t *address);

#endif//__DS18B20_H__
