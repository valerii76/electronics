/*
 * =====================================================================================
 *
 *       Filename:  ds18b20.c
 *
 *    Description:  DS18B20 implementation
 *
 *        Version:  1.0
 *        Created:  11/25/2012  3:36:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  LGE
 *
 * =====================================================================================
 */
#include "ds18b20.h"

#include "ds1wire.h"

enum
{
    CONVERT_T = 0x44,
    WRITE_SCRATCHPAD = 0x4E,
    READ_SCRATCHPAD = 0xBE,
    COPY_SCRATCHPAD = 0x48,
    RECAL_E2 = 0xB8,
    READ_POWER_SUPPLY = 0xB4,
};

uint8_t ds18b20_search (void)
{
    return 0;
}

uint8_t ds18b20_device_number (void)
{
    return 0;
}

uint8_t const* ds18b20_device_address (uint8_t i)
{
    return 0;
}

int16_t ds18b20_temperature (uint8_t *address)
{
    return 0;
}
