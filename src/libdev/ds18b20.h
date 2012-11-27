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
#include "ds1wire.h"

enum
{
    DS18B20_OK = 0,
    DS18B20_NO_DEVICES,
};

/*
 * search ds18b20 devices
 */
void ds18b20_search (ds1wire_add_address address);

/*
 * alarm search ds18b20 devices
 */
void ds18b20_alarm_search (ds1wire_add_address address);

/*
 * get temperature from device
 * if address == NULL works only for one device
 */
uint16_t ds18b20_temperature (uint8_t const *address,
                              uint8_t is_parasite_power);

/*
 * read power supply status
 * if address == NULL works only for one device
 */
uint8_t ds18b20_is_parasite_powered (uint8_t const *address);

/*
 * read scratchpad
 * if address == NULL works only for one device
 */
uint8_t ds18b20_read_scratchpad (uint8_t const *address,
                                 uint8_t data[9]);

/*
 * write scratchpad
 * if address == NULL works only for one device
 * data [Th, Tl, config] bytes
 */
uint8_t ds18b20_write_scratchpad (uint8_t const *address, uint8_t const data [3]);

/*
 * copy scratchpad (Th, Tl, config) to eeprom
 * if address == NULL works only for one device
 */
uint8_t ds18b20_copy_scratchpad (uint8_t const *address,
                                 uint8_t is_parasite_power);

/*
 * recall e2 (recall Th, Tl, config from eeprom)
 */
uint8_t ds18b20_recall_e2 (uint8_t const *address);

#endif//__DS18B20_H__
