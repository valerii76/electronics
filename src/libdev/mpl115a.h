/*
 * ===========================================================================
 *
 *       Filename:  mpl115a.h
 *
 *    Description:  Header for MPL115a (barometer)
 *
 *        Version:  1.0
 *        Created:  10/02/2012 09:10:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  3VSoft
 *
 * ===========================================================================
 */
#if !defined (__MPL115A_H__)
#define __MPL115A_H__

#include <avr/io.h>

void
mpl115a_read_coefficients (int16_t *a0,
                           int16_t *b1,
                           int16_t *b2,
                           int16_t *c12);

int16_t
mpl115a_calc_pcomp (int16_t a0, int16_t b1, int16_t b2, int16_t c12);

/* return format 12:4 (for round >>4) */
uint16_t
mpl115a_pressure_kpa (int16_t p);

/* return format 12:4 (for round >>4) */
uint16_t
mpl115a_pressure_mmhg (int16_t p);

#endif//__MPL115A_H__
