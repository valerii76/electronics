/*
 * =====================================================================================
 *
 *       Filename:  ds1wire.c
 *
 *    Description:  One wire interface implementation
 *
 *        Version:  1.0
 *        Created:  11/24/2012  8:38:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valery.volgutov@lge.com
 *        Company:  LGE
 *
 * =====================================================================================
 */
#include "ds1wire.h"
#include "dbg_uart.h"

#include <avr/io.h>
#include <util/delay.h>

#if !defined (DS1WIRE_DDR)
#warning "DS1WIRE_DDR is not defined - set default value (DDRD)"
#define DS1WIRE_DDR DDRD
#endif

#if !defined (DS1WIRE_PIN)
#warning "DS1WIRE_PIN is not defined - set default value (PIND)"
#define DS1WIRE_PIN PIND
#endif

#if !defined (DS1WIRE_LINE)
#warning "DS1WIRE_LINE is not defined - set default value (PD6)"
#define DS1WIRE_LINE PD6
#endif

#if !defined (SBI)
#define SBI(p, b) ((p) |= 1 << (b))
#endif

#if !defined (CBI)
#define CBI(p, b) ((p) &= ~(1 << (b)))
#endif


enum
{
    SEARCH_ROM = 0xF0,
    READ_ROM = 0x33,
    MATCH_ROM = 0x55,
    SKIP_ROM = 0xCC,
    ALARM_SEARCH = 0xEC,
};

static uint8_t
_ds1wire_receive_bit (void)
{
    uint8_t bit = 0;

    /* start frame */
    SBI (DS1WIRE_DDR, DS1WIRE_LINE);
    _delay_us (5);
    CBI (DS1WIRE_DDR, DS1WIRE_LINE);

    /* wait response from device */
    _delay_us (5);

    if (ds1wire_line_status () == DS1WIRE_HIGH)
        bit = 1;

    /* wait for end of frame */
    _delay_us (50);

    return bit;
}

static void
_ds1wire_send_bit (uint8_t bit)
{
    if (bit)
    {
        SBI (DS1WIRE_DDR, DS1WIRE_LINE);
        _delay_us (15);
        CBI (DS1WIRE_DDR, DS1WIRE_LINE);
        _delay_us (45);
    }
    else
    {
        SBI (DS1WIRE_DDR, DS1WIRE_LINE);
        _delay_us (60);
        CBI (DS1WIRE_DDR, DS1WIRE_LINE);
    }
}

uint8_t ds1wire_start ()
{
    /* send reset pulse */
    SBI (DS1WIRE_DDR, DS1WIRE_LINE);
    _delay_us (480);
    CBI (DS1WIRE_DDR, DS1WIRE_LINE);

    /* wait answer from device */
    _delay_us (60);

    /* check device answer */
    if (ds1wire_line_status () == DS1WIRE_HIGH)
    {
        return DS1WIRE_NO_DEVICES;
    }

    /* wait when device drop line */
    _delay_us (240);

    return DS1WIRE_OK;
}

void ds1wire_send_byte (uint8_t b)
{
    uint8_t i = 8;

    for (; i--; b >>= 1)
    {
        _ds1wire_send_bit (b & 0x1);

        /* delay between frames */
        _delay_us (5);
    }
}

uint8_t ds1wire_receive_byte ()
{
    uint8_t i = 8;
    uint8_t b = 0;

    for (; i--;)
    {
        if (_ds1wire_receive_bit ())
            b |= 0x80;

        if (i > 0)
            b >>= 1;

        /* delay between frames */
        _delay_us (5);
    }

    return b;
}

uint8_t ds1wire_line_status (void)
{
    return ((DS1WIRE_PIN & (1 << DS1WIRE_LINE)) ? DS1WIRE_HIGH : DS1WIRE_LOW);
}

void ds1wire_search_rom (ds1wire_add_address add_func)
{
    uint8_t ROM_NO [8];
    uint8_t id_bit;
    uint8_t cmp_id_bit;
    uint8_t id_bit_number;
    uint8_t last_zero;
    uint8_t last_device_flag;
    uint8_t last_disrepancy;
    uint8_t last_family_disrepancy;
    uint8_t search_direction;
    uint8_t search_result;
    uint8_t rom_byte_mask;
    uint8_t rom_byte_number;
    uint8_t crc8;

    if (!add_func)
        return;

    dbg_uart_send_string ("ds1wire_search_rom...start");

    last_disrepancy = 0;
    last_device_flag = 0;
    last_family_disrepancy = 0;

    do
    {
        /* initialize for search */
        id_bit_number = 1;
        last_zero = 0;
        rom_byte_number = 0;
        rom_byte_mask = 1;
        search_result = 0;
        crc8 = 0;

        if (ds1wire_start () != DS1WIRE_OK)
            return;

        /* search all ROM */
        ds1wire_send_byte (SEARCH_ROM);

        do
        {
            /* read bit */
            id_bit = _ds1wire_receive_bit ();
            _delay_us (5);
            cmp_id_bit = _ds1wire_receive_bit ();
            _delay_us (5);

            /* No 1 wire devices */
            if (id_bit && cmp_id_bit)
                break;

            if (id_bit != cmp_id_bit)
                search_direction = id_bit;
            else
            {
                if (id_bit_number < last_disrepancy)
                    search_direction = ((ROM_NO [rom_byte_number] & rom_byte_mask) > 0);
                else
                    search_direction = id_bit_number == last_disrepancy;

                if (search_direction == 0)
                {
                    last_zero = id_bit_number;

                    if (last_zero > 9)
                        last_family_disrepancy = last_zero;
                }
            }

            if (search_direction)
                ROM_NO [rom_byte_number] |= rom_byte_mask;
            else
                ROM_NO [rom_byte_number] &= ~rom_byte_mask;

            _ds1wire_send_bit (search_direction);
            _delay_us (5);

            ++id_bit_number;
            rom_byte_mask <<= 1;

            if (rom_byte_mask == 0)
            {
                ++rom_byte_number;
                rom_byte_mask = 1;
            }
        }
        while (rom_byte_number < 8);

        if (!((id_bit_number < 65) || (crc8 != 0)))
        {
            /* if search successful so set last_disrepancy, search_result,
             * last_device_flag */
            last_disrepancy = last_zero;

            /* Check last device */
            if (last_disrepancy == 0)
                last_device_flag = 1;

            search_result = 1;
        }

        if (search_result)
        {
            add_func (ROM_NO);
        }

    }
    while (!last_device_flag);

    dbg_uart_send_string ("ds1wire_search_rom...done");
}
