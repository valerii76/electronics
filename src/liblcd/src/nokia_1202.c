/*
 * =====================================================================================
 *
 *       Filename:  nokia_1202.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  24.06.2012 11:54:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  3VSoft
 *
 * =====================================================================================
 */
#include "nokia_1202.h"

#include <avr/pgmspace.h>
#include <util/delay.h>

#if !defined (LCD_PORT)
#warning "LCD_PORT is not defined - set default value (PORTD)"
#define LCD_PORT PORTD
#endif

#if !defined (LCD_DDR)
#warning "LCD_DDR is not defined - set default value (DDRD)"
#define LCD_DDR DDRD
#endif

#if !defined (LCD_CS)
#warning "LCD_CS is not defined - set default value (PD0)"
#define LCD_CS PD0
#endif

#if !defined (LCD_SCLK)
#warning "LCD_SCLK is not defined - set default value (PD1)"
#define LCD_SCLK PD1
#endif

#if !defined (LCD_SDA)
#warning "LCD_SDA is not defined - set default value (PD2)"
#define LCD_SDA PD2
#endif

#if !defined (SBI)
#define SBI(p, b) ((p) |= 1 << (b))
#endif

#if !defined (CBI)
#define CBI(p, b) ((p) &= ~(1 << (b)))
#endif

/* delay 6ms */
static void
_lcd_delay (void)
{
    //_delay_ms(60);
    //unsigned int a, c;
    //for (a=0; a<100; a++)
    //{
        //c++;
    //}
}

/* send byte to LCD */
void
lcd_byte (uint8_t i)
{
    uint8_t d,c;

    for (c = 0; c < 8; ++c)
    {
        d = i & 0x80;
        if (d == 0)
        {
            CBI (LCD_PORT, LCD_SDA);
        }
        else
        {
            SBI (LCD_PORT, LCD_SDA);
        }
        SBI (LCD_PORT, LCD_SCLK);
        CBI (LCD_PORT, LCD_SCLK);
        i = i << 1;
    }
}

/* send command to LCD */
void
lcd_cmd (uint8_t i)
{
    CBI (LCD_PORT, LCD_SCLK);
    CBI (LCD_PORT, LCD_CS);
    CBI (LCD_PORT, LCD_SDA);
    SBI (LCD_PORT, LCD_SCLK);
    CBI (LCD_PORT, LCD_SCLK);

    lcd_byte (i);
}

/* send data to LCD */
void
lcd_data (uint8_t i)
{
    CBI (LCD_PORT, LCD_SCLK);
    CBI (LCD_PORT, LCD_CS);
    SBI (LCD_PORT, LCD_SDA);
    SBI (LCD_PORT, LCD_SCLK);
    CBI (LCD_PORT, LCD_SCLK);

    lcd_byte (i);
}

/* LCD clean */
void
lcd_clr (void)
{
    uint16_t i;

    /* Page address set */
    lcd_cmd (0xB0);
    SBI (LCD_PORT, LCD_CS);

    /* colum address set */
    lcd_cmd (0x10);
    lcd_cmd (0x00);
    SBI (LCD_PORT, LCD_CS);

    for (i = 0; i < 864; i++)
    {
        lcd_data (0);
    }
    SBI (LCD_PORT, LCD_CS);
}

/* set cursor position */
void
lcd_pos (uint8_t row, uint8_t col)
{

    /* Page address set */
    lcd_cmd (0xB0 | (row & 0x0F));
    SBI (LCD_PORT, LCD_CS);
    /* Sets the DDRAM colum address - upper 3-bit */
    lcd_cmd (0x10 | (col >> 4));
    /* lower 4-bit */
    lcd_cmd (0x00 | (col & 0x0F));
    SBI (LCD_PORT, LCD_CS);
}

/* LCD init */
void
lcd_init (void)
{
    SBI (LCD_DDR, LCD_CS);
    SBI (LCD_DDR, LCD_SCLK);
    SBI (LCD_DDR, LCD_SDA);

    SBI (LCD_PORT, LCD_CS);
    CBI (LCD_PORT, LCD_SCLK);

    _lcd_delay ();
    _lcd_delay ();

    /* reset */
    lcd_cmd (0xE2);
    SBI (LCD_PORT, LCD_CS);
    _lcd_delay ();
    _lcd_delay ();

    /* multiple factor x4 */
    lcd_cmd (0x3D);
    SBI (LCD_PORT, LCD_CS);
    _lcd_delay ();
    _lcd_delay ();
    lcd_cmd (0x01);
    SBI (LCD_PORT, LCD_CS);
    _lcd_delay ();
    _lcd_delay ();

    /* power saver off */
    lcd_cmd (0xA4);
    SBI (LCD_PORT, LCD_CS);
    _lcd_delay ();

    /* normal DRAM */
    lcd_cmd (0xA6);
    SBI (LCD_PORT, LCD_CS);

    /* normal mode */
    lcd_cmd (0xA4);
    SBI (LCD_PORT, LCD_CS);

    /* col normal */
    lcd_cmd (0xA0);
    SBI (LCD_PORT, LCD_CS);

    /* driver normal */
    lcd_cmd (0xC0);
    SBI (LCD_PORT, LCD_CS);

    /* VOR def */
    lcd_cmd (0x24);
    SBI (LCD_PORT, LCD_CS);

    /* contrast */
    lcd_cmd (0xE1);
    /* def */
    lcd_cmd (0x80);
    SBI (LCD_PORT, LCD_CS);

    /* El vol - def */
    lcd_cmd (0x90);
    SBI (LCD_PORT, LCD_CS);

    /* poser control set */
    lcd_cmd(0x2F);
    SBI (LCD_PORT, LCD_CS);

    /* LCD display on */
    lcd_cmd (0xAF);
    SBI (LCD_PORT, LCD_CS);

    lcd_clr ();

    lcd_pos (0, 0);

    SBI (LCD_PORT, LCD_CS);
}

/* draw line */
void
lcd_draw_line (uint8_t xn, uint8_t yn, uint8_t xk, uint8_t yk)
{
    uint8_t data;
    uint8_t push;

    int16_t s;
    int8_t dx, dy, kl, sx, sy;
    uint8_t swap, incr1, incr2;

    sx = 0;
    dx = xk - xn;
    if (dx < 0)
    {
        dx = -dx;
        sx = -1;
    }
    else if (dx > 0)
        sx = 1;

    sy = 0;
    dy = yk - yn;
    if (dy < 0)
    {
        dy = -dy;
        sy = -1;
    }
    else if (dy > 0)
        sy = 1;

    swap = 0;
    kl = dx;
    s = dy;
    if (kl <  s)
    {
        dx = s;
        dy = kl;
        kl = s;
        swap = 1;
    }

    incr1 = dy << 1;
    s = incr1 - dx;
    incr2 = dx << 1;

    dx = 8;
    lcd_pos (xn >> 3, yn);
    data = 1 << (xn & 0x7);

    while (--kl >= 0)
    {
        push = 0;
        if (s >= 0)
        {
            if (swap)
            {
                xn += sx;
                --dx;
            }
            else
            {
                yn += sy;
                push = 1;
            }
            s -= incr2;
        }
        if (swap)
        {
            yn += sy;
            push = 1;
        }
        else
        {
            xn += sx;
            --dx;
        }
        s += incr1;

        dy = 1 << (xn & 0x7);

        if (dx == 0)
        {
            push = 1;
            dx = 8;
        }
        if (push)
        {
            lcd_data (data);
            lcd_pos (xn >> 3, yn);
            data = dy;
        }
        else
            data |= dy;
    }
    lcd_data (data);
}

#if defined (BUILDIN_FONT)

#if 0

#include "font.h"
#include "font_15x24.h"
#include "font_15x24_5.h"

/* print symbol (6x8) */
void
lcd_char (uint8_t c)
{
    uint8_t line;
    uint8_t ch;
    uint8_t const *f = (uint8_t const*) &(font6_8[(c - 32) * 6]);

    for (line = 0; line < 6; ++line, ++f)
    {
        ch = pgm_read_byte (f);
        lcd_data (ch);
    }
    SBI (LCD_PORT, LCD_CS);
}

/* print string (null terminated) */
void
lcd_string_ram (char const *str)
{
    while (*str)
    {
        lcd_char (*str);
        ++str;
    }
}

/* print string (null terminated) */
void
lcd_string_pgm (char const *str)
{
    while (pgm_read_byte (str))
    {
        lcd_char (pgm_read_byte (str));
        ++str;
    }
}

/* print big (16x24) symbol */
void
lcd_big_char (uint8_t row, uint8_t col, char chr)
{
    uint8_t const *f0;
    uint8_t const *f;
    uint8_t r, c, y;
    uint8_t ch;
    y = (chr & 0x0F);

    if (y < 6)
        f0 = Tahoma15x24 + y * 45;
    else
        f0 = Tahoma15x24_5 + (y - 6) * 45;

    for (r = 0; r < 3; ++r)
    {
        f = f0 + r;
        lcd_pos ((row + r), col);
        for (c = 0; c < 14; ++c)
        {
            ch = pgm_read_byte (f);
            lcd_data (ch);
            f = f + 3;
        }
    }
    SBI (LCD_PORT, LCD_CS);
}

#else

#include "font_ostin16.h"
#define ARR_SIZE(x) sizeof (x) / (sizeof ((x)[0]))


static void
lcd_debug_led_flash (uint8_t n)
{
    SBI (DDRD, PD0);

    while (n--)
    {
        SBI (PORTD, PD0);
        _delay_ms (500);
        CBI (PORTD, PD0);
        _delay_ms (500);
    }
}


static void
lcd_find_char (uint8_t const *font, uint8_t ch, uint8_t **data)
{
    uint8_t w, h;
    uint8_t i = 0;
    uint8_t *f = (uint8_t*) &(font[1]);
    *data = 0;

    for (; i < font [0]; ++i)
    {
        if (pgm_read_byte (&f [0]) == ch)
        {
            /*lcd_debug_led_flash (3);*/
            *data = &f [1];
            return;
        }
        h = pgm_read_byte (&f [1]);
        w = h & 0x3F;
        h >>= 6;
        f += w * h + 2;
    }
}

void
lcd_char (uint8_t c, uint8_t row, uint8_t *col)
{
    uint8_t line;
    uint8_t ch;
    uint8_t w;
    uint8_t h;
    uint8_t *data;


    lcd_find_char (font_Octin16, c, &data);

    if (!data)
        return;


    h = pgm_read_byte (data);

    w = h & 0x3F;
    h >>= 6;
    ++data;

    for (; h--;)
    {
        lcd_pos (row++, *col);
        for (line = 0; line < w; ++line, ++data)
        {
            ch = pgm_read_byte (data);
            lcd_data (ch);
        }
    }
    *col += w;
    SBI (LCD_PORT, LCD_CS);
}

/* print string (null terminated) */
void
lcd_string_ram (char const *str, uint8_t row, uint8_t col)
{
    uint8_t c;
    uint8_t sp = pgm_read_byte (&font_Octin16 [ARR_SIZE (font_Octin16) - 1]);
    while (c = *str)
    {
        if (c == ' ')
            col += sp;
        else
        {
            ++col;
            lcd_char (*str, row, &col);
        }
        ++str;
    }
}

/* print string (null terminated) */
void
lcd_string_pgm (char const *str, uint8_t row, uint8_t col)
{
    uint8_t c;
    uint8_t sp = pgm_read_byte (&font_Octin16 [ARR_SIZE (font_Octin16) - 1]);
    lcd_debug_led_flash (sp);

    while (c = pgm_read_byte (str))
    {
        if (c == ' ')
            col += sp;
        else
        {
            ++col;
            lcd_char (pgm_read_byte (str), row, &col);
        }
        ++str;
    }
}

#endif

#endif
