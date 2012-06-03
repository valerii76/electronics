/* LCD Nokia 1202 library */

#if !defined (__NOKIA_1202_H__)
#define __NOKIA_1202_H__

#include "lcd/font.h"
#include "lcd/font_15x24.h"
#include "lcd/font_15x24_5.h"

#if !defined (LCD_PORT)
#warning "LCD_PORT is not defined - set default value (PORTD)"
#define LCD_PORT PORTD
#endif

#if !defined (LCD_DDR)
#warning "LCD_DDR is not defined - set default value (DDRD)"
#define LCD_DDR DDRD
#endif

#if !defined (CS)
#warning "CS is not defined - set default value (PD0)"
#define CS_PIN PD0
#endif

#if !defined (SCLK)
#warning "SCLK is not defined - set default value (PD1)"
#define SCLK_PIN PD1
#endif

#if !defined (SDA)
#warning "SDA is not defined - set default value (PD2)"
#define SDA_PIN PD2
#endif

#if !defined (SBI)
#define SBI(p, b) ((p) |= 1 << (b))
#endif

#if !defined (CBI)
#define CBI(p, b) ((p) &= ~(1 << (b)))
#endif

/* delay 6ms */
void
delay ()
{
    //_delay_ms(60);
    //unsigned int a, c;
    //for (a=0; a<100; a++)
    //{
        //c++;
    //}
}

/* send byte to LCD */
inline void
lcd_byte (uint8_t i)
{
    uint8_t d,c;

    for (c = 0; c < 8; ++c)
    {
        d = i & 0x80;
        if (d == 0)
        {
            CBI (LCD_PORT, SDA);
        }
        else
        {
            SBI (LCD_PORT, SDA);
        }
        SBI (LCD_PORT, SCLK);
        CBI (LCD_PORT, SCLK);
        i = i << 1;
    }
}

/* send command to LCD */
void
lcd_cmd (uint8_t i)
{
    CBI (LCD_PORT, SCLK);
    CBI (LCD_PORT, CS);
    CBI (LCD_PORT, SDA);
    SBI (LCD_PORT, SCLK);
    CBI (LCD_PORT, SCLK);

    lcd_byte (i);
}

/* send data to LCD */
void
lcd_data (uint8_t i)
{
    CBI (LCD_PORT, SCLK);
    CBI (LCD_PORT, CS);
    SBI (LCD_PORT, SDA);
    SBI (LCD_PORT, SCLK);
    CBI (LCD_PORT, SCLK);

    lcd_byte (i);
}

/* LCD clean */
void
lcd_clr ()
{
    uint16_t i;

    /* Page address set */
    lcd_cmd (0xB0);
    SBI (LCD_PORT, CS);

    /* colum address set */
    lcd_cmd (0x10);
    lcd_cmd (0x00);
    SBI (LCD_PORT, CS);

    for (i = 0; i < 864; i++)
    {
        lcd_data (0);
    }
    SBI (LCD_PORT, CS);
}

/* set cursor position */
void
lcd_pos (uint8_t row, uint8_t col)
{

    /* Page address set */
    lcd_cmd (0xB0 | (row & 0x0F));
    SBI (LCD_PORT, CS);
    /* Sets the DDRAM colum address - upper 3-bit */
    lcd_cmd (0x10 | (col >> 4));
    /* lower 4-bit */
    lcd_cmd (0x00 | (col & 0x0F));
    SBI (LCD_PORT, CS);
}

/* LCD init */
void
lcd_init ()
{
    SBI (LCD_DDR, CS);
    SBI (LCD_DDR, SCLK);
    SBI (LCD_DDR, SDA);

    SBI (LCD_PORT, CS);
    CBI (LCD_PORT, SCLK);

    delay ();
    delay ();

    /* reset */
    lcd_cmd (0xE2);
    SBI (LCD_PORT, CS);
    delay ();
    delay ();

    /* multiple factor x4 */
    lcd_cmd (0x3D);
    SBI (LCD_PORT, CS);
    delay ();
    delay ();
    lcd_cmd (0x01);
    SBI (LCD_PORT, CS);
    delay ();
    delay ();

    /* power saver off */
    lcd_cmd (0xA4);
    SBI (LCD_PORT, CS);
    delay ();

    /* normal DRAM */
    lcd_cmd (0xA6);
    SBI (LCD_PORT, CS);

    /* normal mode */
    lcd_cmd (0xA4);
    SBI (LCD_PORT, CS);

    /* col normal */
    lcd_cmd (0xA0);
    SBI (LCD_PORT, CS);

    /* driver normal */
    lcd_cmd (0xC0);
    SBI (LCD_PORT, CS);

    /* VOR def */
    lcd_cmd (0x24);
    SBI (LCD_PORT, CS);

    /* contrast */
    lcd_cmd (0xE1);
    /* def */
    lcd_cmd (0x80);
    SBI (LCD_PORT, CS);

    /* El vol - def */
    lcd_cmd (0x90);
    SBI (LCD_PORT, CS);

    /* poser control set */
    lcd_cmd(0x2F);
    SBI (LCD_PORT, CS);

    /* LCD display on */
    lcd_cmd (0xAF);
    SBI (LCD_PORT, CS);

    lcd_clr ();

    lcd_pos (0, 0);

    SBI (LCD_PORT, CS);
}

/* print symbol (6x8) */
void
lcd_char (char c)
{
    uint8_t line;
    uint8_t ch;
    uint8_t const *f = (uint8_t const*) &(font6_8[(c - 32) * 6]);

    for (line = 0; line < 6; ++line, ++f)
    {
        ch = pgm_read_byte (f);
        lcd_data (ch);
    }
    SBI (LCD_PORT, CS);
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
    SBI (LCD_PORT, CS);
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

#endif//__NOKIA_1202_H__
