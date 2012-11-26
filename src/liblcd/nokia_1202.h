/* LCD Nokia 1202 library */

#if !defined (__NOKIA_1202_H__)
#define __NOKIA_1202_H__

#include <avr/io.h>

#if !defined (FONT_DATA_STRUCT)
#define FONT_DATA_STRUCT

typedef struct font_data
{
    unsigned char code;
    unsigned char size;
    unsigned char const *data;
} font_data_t;

#endif

/* LCD clean */
void lcd_clr (void);

/* set cursor position */
void lcd_pos (uint8_t row, uint8_t col);

/* LCD init */
void lcd_init (void);

/* send command to LCD */
void lcd_cmd (uint8_t i);

/* send data to LCD */
void lcd_data (uint8_t i);

/* set current font */
void lcd_set_font (font_data_t const *font, uint8_t font_size);

#if 0
/* draw line */
void lcd_draw_line (uint8_t xn, uint8_t yn, uint8_t xk, uint8_t yk);
#endif

/* print string (null terminated) */
void lcd_string_ram (char const *str, uint8_t row, uint8_t col);

/* print string (null terminated) */
void lcd_string_pgm (char const *str, uint8_t row, uint8_t col);

#endif//__NOKIA_1202_H__
