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
 *        Company:  3VSoft
 *
 * =====================================================================================
 */
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "config.h"

#include "nokia_1202.h"
/*#include "dbg_flash.h"*/
#include "dbg_uart.h"

#include <util/delay.h>

#include "font_5thagent12.h"
/*#include "font_5thagent24.h"*/

int main (int argc, char *argv[])
{
    dbg_uart_init (2400);

    lcd_init();
    lcd_clr();

    lcd_set_font (font_5thagent12, FONT_5THAGENT12_NUM_GLYPS);
    lcd_string_pgm (PSTR ("0123456789"), (uint8_t) 0, (uint8_t) 0);

    /*lcd_set_font (font_5thagent24, FONT_5THAGENT24_NUM_GLYPS);*/
    /*lcd_string_pgm (PSTR ("9789"), (uint8_t) 1, (uint8_t) 0);*/

    /*lcd_set_font (font_5thagent12, FONT_5THAGENT12_NUM_GLYPS);*/
    /*lcd_string_pgm (PSTR ("ABCD"), (uint8_t) 3, (uint8_t) 0);*/

    /*lcd_set_font (font_5thagent24, FONT_5THAGENT24_NUM_GLYPS);*/
    /*lcd_string_pgm (PSTR ("ABCD"), (uint8_t) 4, (uint8_t) 0);*/

    return 0;
}
