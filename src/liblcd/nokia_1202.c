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

static font_data_t const *g_current_font;
static uint8_t g_current_font_size;

#define ARR_SIZE(x) sizeof (x) / (sizeof ((x)[0]))

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
    _delay_ms(60);
}

/* send byte to LCD */
static void
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

#if 0
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
#endif

static uint8_t
lcd_find_char (uint8_t ch, font_data_t *data)
{
    uint8_t mid;
    uint8_t start = 0;
    uint8_t end = g_current_font_size;

    if (!g_current_font_size)
        return 0;

    memcpy_P (data, &g_current_font [0], sizeof (font_data_t));
    if (data->code > ch)
        return 0;

    memcpy_P (data, &g_current_font [end - 1], sizeof (font_data_t));
    if (data->code < ch)
        return 0;

    while (start < end)
    {
        mid = start + ((end - start) >> 1);
        memcpy_P (data, &g_current_font [mid], sizeof (font_data_t));

        if (data->code == ch)
            return 1;

        if (data->code > ch)
            end = mid;
        else
            start = mid + 1;
    }

    return 0;
}

static void
lcd_char (uint8_t c, uint8_t row, uint8_t *col)
{
    uint8_t line;
    uint8_t ch;
    uint8_t w;
    uint8_t h;
    font_data_t data;
    uint8_t const *glyph = 0;

    if (!lcd_find_char (c, &data))
        return;

    h = data.size;

    w = h & 0x3F;
    h >>= 6;
    glyph = data.data;

    for (; h--;)
    {
        lcd_pos (row++, *col);
        for (line = 0; line < w; ++line, ++glyph)
        {
            ch = pgm_read_byte (glyph);
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
    while ((c = *str))
    {
        ++col;
        lcd_char (*str, row, &col);
        ++str;
    }
}

/* print string (null terminated) */
void
lcd_string_pgm (char const *str, uint8_t row, uint8_t col)
{
    uint8_t c;

    while ((c = pgm_read_byte (str)))
    {
        ++col;
        lcd_char (pgm_read_byte (str), row, &col);
        ++str;
    }
}

void
lcd_set_font (font_data_t const *font, uint8_t font_size)
{
    g_current_font = font;
    g_current_font_size = font_size;
}
