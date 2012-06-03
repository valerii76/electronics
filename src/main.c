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

#include <stdlib.h>

#define LCD_PORT PORTC
#define LCD_DDR DDRC
#define CS PC0
#define SCLK PC1
#define SDA PC2

#define SBI(p, b) ((p) |= 1 << (b))
#define CBI(p, b) ((p) &= ~(1 << (b)))

#include "lcd/nokia_1202.h"

int main ()
{

    /*int8_t x, y, w, h;*/

    lcd_init();

    /*lcd_string_pgm (PSTR("Valerii76"));*/

    /*while (1)*/
    /*{*/
        /*x = rand () % 68;*/
        /*y = rand () % 96;*/

        /*w = rand () % (68 - x);*/
        /*h = rand () % (96 - y);*/

        /*lcd_draw_line (x, y, x + w, y + h);*/
    /*}*/


    lcd_draw_line (0, 0, 68, 96);
    lcd_draw_line (68, 0, 0, 96);


    return 0;
}
