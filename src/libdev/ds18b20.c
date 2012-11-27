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

#include <util/delay.h>

enum
{
    FAMILY_CODE = 0x28,
};

enum
{
    CONVERT_T = 0x44,
    WRITE_SCRATCHPAD = 0x4E,
    READ_SCRATCHPAD = 0xBE,
    COPY_SCRATCHPAD = 0x48,
    RECALL_E2 = 0xB8,
    READ_POWER_SUPPLY = 0xB4,
};

void (*device_address_func_save) (uint8_t const *address);

void search_ds18b20 (uint8_t const *address)
{
    if (address [0] == FAMILY_CODE)
        device_address_func_save (address);
}

void
ds18b20_search (ds1wire_add_address address)
{
    if (!address)
        return;

    device_address_func_save = address;

    ds1wire_search_rom (search_ds18b20);
}

void
ds18b20_alarm_search (ds1wire_add_address address)
{
    if (!address)
        return;

    device_address_func_save = address;

    ds1wire_alarm_search (search_ds18b20);
}

uint16_t
ds18b20_temperature (uint8_t const *address,
                     uint8_t is_parasite_power)
{
    uint8_t temp[2];

    if (ds1wire_start () != DS1WIRE_OK)
        return DS18B20_NO_DEVICES;

    if (address)
        ds1wire_match_rom (address);
    else
        ds1wire_skip_rom ();

    ds1wire_send_byte (CONVERT_T);

    /* need to wait when convert is done */
    if (is_parasite_power)
    {
        /* need to strong pullup device
           how we do not implement it */
        _delay_us (10);
    }
    else
    {
        while (ds1wire_line_status () == DS1WIRE_LOW)
            ;
    }

    ds1wire_start ();

    if (address)
        ds1wire_match_rom (address);
    else
        ds1wire_skip_rom ();

    ds1wire_send_byte (READ_SCRATCHPAD);

    temp [0] = ds1wire_receive_byte ();
    temp [1] = ds1wire_receive_byte ();

    return (temp [0] | (temp [1] << 8));
}

uint8_t
ds18b20_is_parasite_powered (uint8_t const *address)
{
    if (ds1wire_start () != DS1WIRE_OK)
        return DS18B20_NO_DEVICES;

    if (address)
        ds1wire_match_rom (address);
    else
        ds1wire_skip_rom ();

    ds1wire_send_byte (READ_POWER_SUPPLY);

    return (ds1wire_line_status () == DS1WIRE_LOW);
}

uint8_t
ds18b20_read_scratchpad (uint8_t const *address, uint8_t data[9])
{
    uint8_t i;

    if (ds1wire_start () != DS1WIRE_OK)
        return DS18B20_NO_DEVICES;

    if (address)
        ds1wire_match_rom (address);
    else
        ds1wire_skip_rom ();

    ds1wire_send_byte (READ_SCRATCHPAD);

    for (i = 0; i < 9; ++i)
        data [i] = ds1wire_receive_byte ();

    return DS18B20_OK;
}

uint8_t
ds18b20_write_scratchpad (uint8_t const *address, uint8_t const data [3])
{
    if (ds1wire_start () != DS1WIRE_OK)
        return DS18B20_NO_DEVICES;

    if (address)
        ds1wire_match_rom (address);
    else
        ds1wire_skip_rom ();

    ds1wire_send_byte (WRITE_SCRATCHPAD);

    ds1wire_send_byte (data [0]);
    ds1wire_send_byte (data [1]);
    ds1wire_send_byte (data [2]);

    return DS18B20_OK;
}

uint8_t
ds18b20_copy_scratchpad (uint8_t const *address,
                         uint8_t is_parasite_power)
{
    if (ds1wire_start () != DS1WIRE_OK)
        return DS18B20_NO_DEVICES;

    if (address)
        ds1wire_match_rom (address);
    else
        ds1wire_skip_rom ();

    ds1wire_send_byte (COPY_SCRATCHPAD);

    if (is_parasite_power)
    {
        /* need to strong pullup device
           how we do not implement it */
        _delay_us (10);
    }
    else
    {
        while (ds1wire_line_status () == DS1WIRE_LOW)
            ;
    }

    return DS18B20_OK;
}

uint8_t
ds18b20_recall_e2 (uint8_t const *address)
{
    if (ds1wire_start () != DS1WIRE_OK)
        return DS18B20_NO_DEVICES;

    if (address)
        ds1wire_match_rom (address);
    else
        ds1wire_skip_rom ();

    ds1wire_send_byte (RECALL_E2);

    while (ds1wire_line_status () == DS1WIRE_LOW)
        ;

    return DS18B20_OK;
}
