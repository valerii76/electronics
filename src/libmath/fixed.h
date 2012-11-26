/*
 * =====================================================================================
 *
 *       Filename:  fixed.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05.06.2012 21:44:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  3VSoft
 *
 * =====================================================================================
 */

#if !defined __FIXED_H__
#define __FIXED_H__

#define SICO 0
#define SQRT 0

#define FIXED_INT_PART 0xff00
#define FIXED_PREC_PART 0xff
#define FIXED_PREC 8
#define FIXED_INT 8
#define FIXED_1 (1 << FIXED_PREC)
typedef int16_t fixed_t;

#define FIXED2INT(a) (a >> FIXED_PREC)
#define FIXED2FLOAT(a) ((float)(a) / FIXED_1)
#define INT2FIXED(a) ((a) << FIXED_PREC)
#define FLOAT2FIXED(a) ((fixed_t)((a) * FIXED_1))


fixed_t
fixed_mul (fixed_t a, fixed_t b)
{
    return (fixed_t) (((int32_t)(a) * b) >> FIXED_PREC);
}

fixed_t
fixed_div (fixed_t a, fixed_t b)
{
    return (fixed_t)((int32_t)(a << FIXED_PREC) / b);
}

#if SQRT
fixed_t
fixed_sqrt (fixed_t a)
{
    int32_t b = a << FIXED_PREC;
    int32_t temp, div;
    uint16_t res;

    if (b <= 0)
        return 0;

    if (a & FIXED_INT_PART)
        div = a;
    else
        div = b >> ((FIXED_PREC / 2));

    res = div;

    while (1)
    {
        temp = b / div + div;
        div = temp >> 1;
        div += temp & 1;
        if (res > div)
            res = (uint16_t)div;
        else
            return (fixed_t)res;
    }
}
#endif

#if SICO
#define M_PI 3.141592653589793
#define FM_PI  (FLOAT2FIXED (M_PI))
#define FM_PI2 (FLOAT2FIXED (M_PI / 2))
#define FM_PI4 (FLOAT2FIXED (M_PI / 4))
#define MFRAC 4
static void
_fixed_sico (fixed_t a, fixed_t *s, fixed_t *c)
{
    char n, n2;
    fixed_t a2, t;

    t = 0;
    a >>= 1;
    a2 = fixed_mul (a, a);
    n = MFRAC - 1;
    n2 = (n << 1) + 1;

    for (; n >= 0; --n)
    {
        if (n > 0)
            t = fixed_div (a2, (INT2FIXED (n2) - t));
        else
            t = fixed_div (a, (FIXED_1 - t));
        --n2;
        --n2;
    }
    a = fixed_mul (t, t);
    a2 = fixed_div (FIXED_1, (a + FIXED_1));
    *s = fixed_mul (t, a2) << 1;
    *c = fixed_mul ((FIXED_1 - a), a2);
}

void
fixed_sico (fixed_t a, fixed_t *s, fixed_t *c)
{
    if (a < FM_PI4)
        _fixed_sico (a, s, c);
    else
        _fixed_sico (FM_PI2 - a, c, s);
}

void
fixed_sico1p (fixed_t a, fixed_t *s, fixed_t *c)
{
    int8_t sign = 0;
    if (a < 0)
    {
        a = -a;
        sign = 1;
    }

    if (a <= FM_PI2)
        fixed_sico (a, s, c);
    else
    {
        fixed_sico (a - FM_PI2, c, s);
        *c = -(*c);
    }
    if (sign)
        *s = -(*s);
}
#endif

#endif//__FIXED_H__
