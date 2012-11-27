/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  main file
 *
 *        Version:  1.0
 *        Created:  14.05.2012 20:55:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  3VSoft
 *
 * =====================================================================================
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "config.h"

#include "dbg_flash.h"
#include "nokia_1202.h"
#include "dbg_uart.h"
#include "twi_master.h"
#include "ds1wire.h"
#include "ds18b20.h"

#include <util/delay.h>

#include "font_5thagent12.h"
#include "font_5thagent24.h"

#include <stdio.h>
#include <stdlib.h>

#include "mpl115a.h"

void show_address (uint8_t const *address)
{
    int i;
    char buf [20];
    for (i = 0; i < 8; ++i)
    {
        itoa (address [i], buf, 16);
        dbg_uart_send (buf [0]);
        if (buf [1] != 0)
            dbg_uart_send (buf [1]);
        else
            dbg_uart_send ('0');
        if (i < 7)
            dbg_uart_send (':');
    }
    dbg_uart_send (0xA);
    dbg_uart_send (0xD);
}

int main (int argc, char *argv[])
{
    char buf [20];

    int16_t a0 = 0;
    int16_t b1 = 0;
    int16_t b2 = 0;
    int16_t c12 = 0;

    sei ();

    dbg_uart_init (2400);

    lcd_init();

    twi_master_initialise ();

    mpl115a_read_coefficients (&a0, &b1, &b2, &c12);

    while (1)
    {
        int16_t pcomp;
        uint16_t kpa;
        uint16_t mmhg;
        uint16_t temp16;

        lcd_clr();

        pcomp = mpl115a_calc_pcomp (a0, b1, b2, c12);

        kpa = mpl115a_pressure_kpa (pcomp);
        mmhg = mpl115a_pressure_mmhg (pcomp);


        lcd_set_font (font_5thagent12, FONT_5THAGENT12_NUM_GLYPS);
        /*lcd_string_ram (itoa (pcomp, buf, 10), (uint8_t) 1, (uint8_t) 0);*/
        lcd_string_ram (itoa (kpa >> 4, buf, 10), (uint8_t) 0, (uint8_t) 0);
        lcd_string_ram (itoa (mmhg >> 4, buf, 10), (uint8_t) 1, (uint8_t) 0);

        /*ds1wire_search_rom (show_address);*/
        /*ds1wire_alarm_search (show_address);*/

        temp16 = ds18b20_temperature (NULL, ds18b20_is_parasite_powered (NULL));

        dbg_uart_send_string (itoa (temp16, buf, 16));

        _delay_ms (1000);
    }

    return 0;
}
