/*
 * ===========================================================================
 *
 *       Filename:  menu.h
 *
 *    Description:  Simple menu implementation for AVR
 *
 *        Version:  1.0
 *        Created:  09/10/2012 09:46:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Valery Volgutov (Valery Volgutov), valerii76@gmail.com
 *        Company:  3VSoft
 *
 * ===========================================================================
 */
#if !defined (__MENU_H__)
#define __MENU_H__

typedef unsigned char menu_key_t;
typedef signed char menu_index_t;
typedef unsigned char menu_bool_t;
typedef unsigned char menu_status_t;
typedef unsigned char menu_item_id_t;
typedef unsigned char menu_item_mask_t;
typedef menu_status_t (*menu_item_action_t)(menu_item_id_t id);
typedef menu_status_t (*menu_item_key_t)(menu_key_t key_data);
typedef struct _menu_item_s
{
    menu_item_id_t id;
    menu_item_action_t action;
    menu_item_key_t key;

    menu_item_mask_t mask;
} menu_item_t;

menu_bool_t menu_is_submenu (menu_item_t *menu, unsigned char n, menu_index_t current);
menu_index_t menu_forward (menu_item_t *menu, unsigned char n, menu_index_t current);
menu_index_t menu_backward (menu_item_t *menu, unsigned char n, menu_index_t current);
menu_index_t menu_up (menu_item_t *menu, unsigned char n, menu_index_t current);
menu_index_t menu_down (menu_item_t *menu, unsigned char n, menu_index_t current);

/* Menu example!!! */
//menu_item_t menu[] =
//{
    //{ 0x01, menu_action, NULL, 0x07 }, [> item1 <]
    //{ 0x02, NULL, NULL,  0x07 },       [> submenu<]
    //{ 0x08, menu_action, NULL, 0x18 }, [> item2 <]
    //{ 0x10, menu_action, NULL, 0x18 }, [> item3 <]
    //{ 0x18, menu_action, NULL, 0x18 }, [> item4 <]
    //{ 0x03, menu_action, NULL, 0x07 }, [> item5 <]
    //{ 0x04, menu_action, NULL, 0x07 }, [> item6 <]
//};


/* Does not work!!! Please do not use it!!! */
#define MENU_START(menu_name, num) menu_item_t menu_##menu_name[] = {

#define MENU_END(menu_name) };

#define MENU_ITEM(item, action, key) { GENERATE_ID, action, key, GENERATE_MASK},

#define MENU_SUBMENU(submenu, num)
#define MENU_SUBMENU_END(submenu)

/* Menu example
 * MENU_START (menu, 4)
 *      <<< group 1 >>>
 *      MENU_ITEM (item1, action, key)
 *      <<< group 2 >>>
 *      MENU_SUBMENU (submenu, 3)
 *              MENU_ITEM (item2, action, key)
 *              MENU_ITEM (item3, action, key)
 *              MENU_ITEM (item4, action, key)
 *      MENU_SUBMENU_END (submenu)
 *      <<< group 1 >>>
 *      MENU_ITEM (item5, action_key)
 *      MENU_ITEM (item6, action_key)
 * MENU_END (menu)
 */

#endif//__MENU_H__
