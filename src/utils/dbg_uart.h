/*
 * ===========================================================================
 *
 *       Filename:  dbg_uart.h
 *
 *    Description:  Debug UART (only for debuging)
 *
 *        Version:  1.0
 *        Created:  09/09/2012 02:43:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  3VSoft
 *
 * ===========================================================================
 */
#if !defined (__DBG_UART_H__)
#define __DBG_UART_H__

#include <avr/io.h>

/* init UART 8data, 1 stop bit */
void dbg_uart_init (uint32_t speed);

/* send data to UART */
void dbg_uart_send (uint8_t c);

/* receive data from UART */
uint8_t dbg_uart_receive (void);

/* send null terminated string to UART */
void dbg_uart_send_string (char const *str);

#endif//__DBG_UART_H__
