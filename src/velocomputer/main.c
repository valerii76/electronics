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

#include <stdlib.h>

#include "nokia_1202.h"
/*#include "math/fixed.h"*/

int main (int argc, char *argv[])
{
    /*fixed_t x = INT2FIXED (34), y = 0, d;*/
    /*int8_t i;*/

    lcd_init();
    lcd_clr();
    /*lcd_draw_line (0, 0, 68, 96);*/
    /*lcd_draw_line (68, 0, 0, 96);*/
    lcd_string_pgm (PSTR ("3VSOFT"), 4, 20);
    /*lcd_char ('W', 0, 0);*/

    /*d = fixed_div (FM_PI << 1, INT2FIXED (96));*/

    /*for (i = 1; i < 96; ++i)*/
    /*{*/
        /*fixed_t s, c;*/
        /*fixed_t new_x = INT2FIXED (34);*/
        /*y += d;*/
        /*fixed_sico (y, &s, &c);*/
        /*new_x += fixed_mul (s, INT2FIXED (34));*/
        /*lcd_draw_line (FIXED2INT (x), i-1, FIXED2INT (new_x), i);*/
        /*x = new_x;*/
    /*}*/

    /*lcd_string_pgm (PSTR("Valerii76"));*/

    /*while (1)*/
    /*{*/
        /*x = rand () % 68;*/
        /*y = rand () % 96;*/

        /*w = rand () % (68 - x);*/
        /*h = rand () % (96 - y);*/

        /*lcd_draw_line (x, y, x + w, y + h);*/
    /*}*/


    /*lcd_draw_line (0, 0, 68, 96);*/
    /*lcd_draw_line (68, 0, 0, 96);*/


    return 0;
}
