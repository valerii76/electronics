/* LCD Nokia 1202 library */

#if !defined (__NOKIA_1202_H__)
#define __NOKIA_1202_H__

#include <avr/io.h>

/* LCD clean */
void lcd_clr (void);

/* set cursor position */
void lcd_pos (uint8_t row, uint8_t col);

/* LCD init */
void lcd_init (void);

/* draw line */
void lcd_draw_line (uint8_t xn, uint8_t yn, uint8_t xk, uint8_t yk);

/* print string (null terminated) */
void lcd_string_ram (char const *str, uint8_t row, uint8_t col);

/* print string (null terminated) */
void lcd_string_pgm (char const *str, uint8_t row, uint8_t col);

#endif//__NOKIA_1202_H__
