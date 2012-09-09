#include <stdio.h>

#define ARR_SIZE(arr) (sizeof (arr) / sizeof ((arr)[0]))

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

#define MENU_START(menu_name) menu_item_t menu_##menu_name[] = {
#define MENU_END(menu_name) }
#define MENU_ITEM(item, action, key) { },

#define MENU_SUBMENU(item)
#define ROOT_MENU(menu)

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

menu_status_t menu_action (menu_item_id_t id);

menu_item_t menu[] =
{
    { 0x01, menu_action, NULL, 0x07 }, /* item1 */
    { 0x02, NULL, NULL,  0x07 },       /* submenu*/
    { 0x08, menu_action, NULL, 0x18 }, /* item2 */
    { 0x10, menu_action, NULL, 0x18 }, /* item3 */
    { 0x18, menu_action, NULL, 0x18 }, /* item4 */
    { 0x03, menu_action, NULL, 0x07 }, /* item5 */
    { 0x04, menu_action, NULL, 0x07 }, /* item6 */
};

menu_bool_t menu_is_submenu (menu_index_t current)
{
    menu_index_t i;
    menu_item_mask_t mask = menu[current].mask;

    if ((current + 1) < ARR_SIZE (menu) &&
            !(menu[current + 1].id & mask) &&
            (menu[current + 1].id > menu[current].id))
        return 1;

    return 0;
}

menu_index_t menu_forward (menu_index_t current)
{
    menu_index_t i;
    menu_item_mask_t mask = menu[current].mask;

    /* find forward */
    for (i = (current + 1); i < ARR_SIZE (menu); ++i)
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

menu_index_t menu_backward (menu_index_t current)
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
    for (i = (current + 1); i < ARR_SIZE (menu); ++i)
    {
        if (menu[i].id & mask)
            current = i;
    }
    return current;
}

menu_index_t menu_up (menu_index_t current)
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

menu_index_t menu_down (menu_index_t current)
{
    if (menu_is_submenu (current))
        return current + 1;

    return current;
}


menu_status_t menu_action (menu_item_id_t id)
{
    printf ("menu: %d\n", id);
    return 0;
}

void full_menu (menu_index_t current)
{
    menu_index_t i = current;
    menu_item_t *item = &menu[current];
    if (menu_is_submenu (current))
    {
        printf ("submenu: %d\n", item->id);
        i = menu_down (current);
        full_menu (i);
    }

    if (item->action)
        item->action (item->id);

    i = menu_forward (i);
    if (i < current)
    {
        current = menu_up(current);
        i = menu_forward (current);
        if (i > current)
            full_menu (i);
    }
    else
        full_menu(i);
}

int menu_process ()
{
    /*menu_index_t i = 0;*/
    /*full_menu (&root);*/
    menu_index_t curr = 0;
    full_menu (curr);
    return 0;
}

int main (int argc, char *argv[])
{
    printf ("menu demo\n");

    while (menu_process())
        ;

    printf ("menu demo exit\n");

    return 0;
}
