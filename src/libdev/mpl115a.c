/*
 * ===========================================================================
 *
 *       Filename:  mpl115a.c
 *
 *    Description:  Implementation MPL115A
 *
 *        Version:  1.0
 *        Created:  10/02/2012 10:30:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  3VSoft
 *
 * ===========================================================================
 */
#include <avr/io.h>
#include <util/delay.h>

#include "mpl115a.h"
#include "twi_master.h"


static int16_t
mpl115a_pcomp (uint16_t padc, uint16_t tadc,
               int16_t a0, int16_t b1, int16_t b2, int16_t c12)
{
    int32_t c12x2, a1, a1x1, y1, a2x2, p;

    padc >>= 6;
    tadc >>= 6;

    c12x2 = (((int32_t) c12) * tadc) >> 11;
    a1 = (int32_t) b1 + c12x2;
    a1x1 = a1 * padc;
    y1 = (((int32_t) a0) << 10) + a1x1;
    a2x2 = (((int32_t) b2) * tadc) >> 1;
    p = (y1 + a2x2) >> 9;

    return (int16_t) p;
}

void
mpl115a_read_coefficients (int16_t *a0,
                           int16_t *b1,
                           int16_t *b2,
                           int16_t *c12)
{
    static uint8_t data [10];

    data [0] = 0xC0;
    data [1] = 0x4;
    twi_start_transceiver_with_data (data, 2);

    data [0] = 0xC1;
    twi_start_transceiver_with_data (data, 9);
    twi_get_data_from_transceiver (data, 9);

    *a0 = (data [1] << 8) | data [2];
    *b1 = (data [3] << 8) | data [4];
    *b2 = (data [5] << 8) | data [6];
    *c12 = (data [7] << 8) | data [8];
}

int16_t
mpl115a_calc_pcomp (int16_t a0, int16_t b1, int16_t b2, int16_t c12)
{
    static uint8_t data [5];
    uint16_t padc, tadc;

    /* start conversion */
    data [0] = 0xC0;
    data [1] = 0x12;
    data [2] = 0;
    twi_start_transceiver_with_data (data, 3);
    _delay_ms (5);

    /* read results */
    data [0] = 0xC0;
    data [1] = 0;
    twi_start_transceiver_with_data (data, 2);

    data [0] = 0xC1;
    twi_start_transceiver_with_data (data, 5);
    twi_get_data_from_transceiver (data, 5);
    padc = (data [1] << 8) | data [2];
    tadc = (data [3] << 8) | data [4];

    return mpl115a_pcomp (padc, tadc, a0, b1, b2, c12);
}

uint16_t
mpl115a_pressure_kpa (int16_t p)
{
    int32_t press = ((((int32_t) p) * 1041) >> 14) + 800;

    return press;
}

uint16_t
mpl115a_pressure_mmhg (int16_t p)
{
    int32_t press;
    press = ((int32_t)mpl115a_pressure_kpa (p)) * 120;

    return press >> 4;
}
