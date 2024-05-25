#include "item.h"

#include <stdlib.h>

Item item_new(char *name, size_t max_amount)
{
    Item i = {0};
    i.name = name;
    i.count = 1;
    i.max_amount = (max_amount == 0) ? 1 : max_amount;
    i.type = ITEM_TYPE_DEFAULT;

    return i;
}

void item_cleanup(Item *i)
{
    switch (i->type) {
        case ITEM_TYPE_WEAPON:
            free(i->item_data.weapon_data);
            break;
        case ITEM_TYPE_PICKAXE:
            free(i->item_data.pickaxe_data);
            break;
        default:
            break;
    }
}

Item item_new_weapon(char *name)
{
    Item i = {0};
    i.name = name;
    i.count = 1;
    i.max_amount = 1;
    i.type = ITEM_TYPE_WEAPON;

    i.item_data = (ItemData){0};
    i.item_data.weapon_data = malloc(sizeof(ItemDataWeapon));
    i.item_data.weapon_data->stab = 32;

    return i;
}

Item item_new_pickaxe(char *name, PickaxeType type)
{
    Item i = {0};
    i.name = name;
    i.count = 1;
    i.max_amount = 1;
    i.type = ITEM_TYPE_PICKAXE;

    i.item_data = (ItemData){0};
    i.item_data.pickaxe_data = malloc(sizeof(ItemDataPickaxe));
    i.item_data.pickaxe_data->type = type;

    return i;
}

char* item_type(Item *i)
{
    switch (i->type) {
        case ITEM_TYPE_DEFAULT: return "Default";
        case ITEM_TYPE_WEAPON: return "Weapon";
        case ITEM_TYPE_TOOL: return "Tool";
        case ITEM_TYPE_PICKAXE: return "Pickaxe";
        default: return "Not Reachable";
    }
}
