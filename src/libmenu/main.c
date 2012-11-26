#include <stdio.h>

#include "menu.h"

#define ARR_SIZE(arr) (sizeof (arr) / sizeof ((arr)[0]))

menu_status_t menu_action (menu_item_id_t id);

MENU_START (main, 4)
    { 0x01, menu_action, NULL, 0x07 }, /* item1 */
    { 0x02, NULL, NULL,  0x07 },       /* submenu*/
    { 0x08, menu_action, NULL, 0x18 }, /* item2 */
    { 0x10, menu_action, NULL, 0x18 }, /* item3 */
    { 0x18, menu_action, NULL, 0x18 }, /* item4 */
    { 0x03, menu_action, NULL, 0x07 }, /* item5 */
    { 0x04, menu_action, NULL, 0x07 }, /* item6 */
MENU_END (main)

menu_status_t menu_action (menu_item_id_t id)
{
    printf ("menu: %d\n", id);
    return 0;
}

void full_menu (menu_index_t current)
{
    menu_index_t i = current;
    menu_item_t *item = &menu_main[current];
    if (menu_is_submenu (menu_main, ARR_SIZE (menu_main), current))
    {
        printf ("submenu: %d\n", item->id);
        i = menu_down (menu_main, ARR_SIZE (menu_main), current);
        full_menu (i);
    }

    if (item->action)
        item->action (item->id);

    i = menu_forward (menu_main, ARR_SIZE (menu_main), i);
    if (i < current)
    {
        current = menu_up (menu_main, ARR_SIZE (menu_main), current);
        i = menu_forward (menu_main, ARR_SIZE (menu_main), current);
        if (i > current)
            full_menu (i);
    }
    else
        full_menu(i);
}

int menu_process (void)
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
