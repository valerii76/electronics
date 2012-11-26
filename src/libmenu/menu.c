/*
 * ===========================================================================
 *
 *       Filename:  menu.c
 *
 *    Description:  Menu implementation
 *
 *        Version:  1.0
 *        Created:  09/10/2012 09:48:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  3VSoft
 *
 * ===========================================================================
 */
#include "menu.h"

menu_bool_t menu_is_submenu (menu_item_t *menu,
                             unsigned char n,
                             menu_index_t current)
{
    menu_item_mask_t mask = menu[current].mask;

    if ((current + 1) < n &&
            !(menu[current + 1].id & mask) &&
            (menu[current + 1].id > menu[current].id))
        return 1;

    return 0;
}

menu_index_t menu_forward (menu_item_t *menu,
                           unsigned char n,
                           menu_index_t current)
{
    menu_index_t i;
    menu_item_mask_t mask = menu[current].mask;

    /* find forward */
    for (i = (current + 1); i < n; ++i)
    {
        if (menu[i].id & mask)
            return i;
    }
    /* find backward */
    for (i = (current - 1); i >= 0; --i)
    {
        if (menu[i].id & mask)
            current = i;
    }

    return current;
}

menu_index_t menu_backward (menu_item_t *menu,
                            unsigned char n,
                            menu_index_t current)
{
    menu_index_t i;
    menu_item_mask_t mask = menu[current].mask;

    /* find backward */
    for (i = (current - 1); i >= 0; --i)
    {
        if (menu[i].id & mask)
            return i;
    }
    /* find forward */
    for (i = (current + 1); i < n; ++i)
    {
        if (menu[i].id & mask)
            current = i;
    }
    return current;
}

menu_index_t menu_up (menu_item_t *menu,
                      unsigned char n,
                      menu_index_t current)
{
    menu_index_t i;
    menu_item_mask_t mask = menu[current].mask;

    /* find backward */
    for (i = (current - 1); i >= 0; --i)
    {
        if (!(menu[i].id & mask))
            return i;
    }

    return current;
}

menu_index_t menu_down (menu_item_t *menu,
                        unsigned char n,
                        menu_index_t current)
{
    if (menu_is_submenu (menu, n, current))
        return current + 1;

    return current;
}
