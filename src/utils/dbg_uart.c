/*
 * ===========================================================================
 *
 *       Filename:  dbg_uart.c
 *
 *    Description:  Debug UART implementation
 *
 *        Version:  1.0
 *        Created:  09/09/2012 02:50:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  3VSoft
 *
 * ===========================================================================
 */
#include <avr/io.h>
#include "dbg_uart.h"

void
dbg_uart_init (uint32_t speed)
{
    speed = F_CPU / 16 / (speed - 1);
    UBRRH = (uint8_t) (speed >> 8);
    UBRRL = (uint8_t) (speed);

    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (0 << UMSEL) | (0 << USBS) | (3 << UCSZ0);
}

void
dbg_uart_send (uint8_t c)
{
    /* wait for empty transmit buffer */
    while (! (UCSRA & (1 << UDRE)))
        ;

    /* put datat into buffer, sends data */
    UDR = c;
}

uint8_t dbg_uart_receive (void)
{
    /* wait for data to be received */
    while ( ! (UCSRA & (1 << RXC)))
        ;

    /* get and return received data from buffer */
    return UDR;
}

void
dbg_uart_send_string (char const *str)
{
    while (*str)
    {
        dbg_uart_send (*str);
        ++str;
    }
    dbg_uart_send (0xA);
    dbg_uart_send (0xD);
}
