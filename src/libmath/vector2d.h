/*
 * =====================================================================================
 *
 *       Filename:  vector2d.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05.06.2012 21:43:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  3VSoft
 *
 * =====================================================================================
 */
#if !defined __VECTOR_2D_H__
#define __VECTOR_2D_H__

#include "math/fixed.h"

typedef struct _vector2d
{
    fixed_t x;
    fixed_t y;
} vector2d_t;

inline void
vector2d_init (vector2d_t *v, fixed_t x, fixed_t y)
{
    v->x = x;
    v->y = y;
}

inline fixed_t
vector2d_dot (vector2d_t *v1, vector2d_t *v2)
{
    return (fixed_t)(fixed_mul(v1->x, v2->x) + fixed_mul (v1->y, v2->y));
}

inline fixed_t
vector2d_length (vector2d_t *v)
{
    fixed_t len = fixed_sqrt (vector2d_dot (v, v));
    return len;
}

inline void
vector2d_normalize (vector2d_t *v)
{
    fixed_t len = vector2d_length (v);
    fixed->x = fixed_div (v->x, len);
    fixed->y = fixed_div (v->y, len);
}

inline fixed_t
vector2d_cross_scalar (vector2d_t *v1, vector2d_t *v2)
{
    return fixed_mul (v1->x, v2->y) - fixed_mul (v1->y, v2->x);
}

inline void
vector2d_cross (vector2d_t *v1, vector2d_t *v2, vector2d_t *res)
{
    res->x = v2->y;
    res->y = -v1->x
}

#endif//__VECTOR_2D_H__
