/* LCD Nokia 1202 library */

#if !defined (__NOKIA_1202_H__)
#define __NOKIA_1202_H__

#include <avr/io.h>

/* send byte to LCD */
void lcd_byte (uint8_t i);

/* send command to LCD */
void lcd_cmd (uint8_t i);

/* send data to LCD */
void lcd_data (uint8_t i);

/* LCD clean */
void lcd_clr (void);

/* set cursor position */
void lcd_pos (uint8_t row, uint8_t col);

/* LCD init */
void lcd_init (void);

/* draw line */
void lcd_draw_line (uint8_t xn, uint8_t yn, uint8_t xk, uint8_t yk);

#if defined(BUILDIN_FONT)

/* print symbol (6x8) */
void lcd_char (uint8_t c);

/* print string (null terminated) */
void lcd_string_ram (char const *str);

/* print string (null terminated) */
void lcd_string_pgm (char const *str);

/* print big (16x24) symbol */
void lcd_big_char (uint8_t row, uint8_t col, char chr);

#endif

#endif//__NOKIA_1202_H__
