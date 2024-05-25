#include "activities.h"
#include "item.h"

#include <stdbool.h>
#include <stdio.h>

ActivityResult activity_mine(Player *p, Mineable m)
{
    if (p->skills.mining.level < m.level_required) {
        return (ActivityResult){ACTIVITY_FAILED_LOW_LEVEL};
    }

    PickaxeType bestPickaxe = PICKAXE_TYPE_NULL;
    if (p->equipped.mainhand.type == ITEM_TYPE_PICKAXE) {
        ItemDataPickaxe *data = p->equipped.mainhand.item_data.pickaxe_data;
        if (data->type > bestPickaxe) {
            bestPickaxe = data->type;
        }
    }

    // Look for a pickaxe in the inventory
    uint16_t foundSlots = 0;
    for (size_t i = 0; i < p->inventory.capacity; i++) {
        if (foundSlots == p->inventory.count) {
            break;
        }
        if (p->inventory.items[i].count == 0) {
            continue;
        }

        if (p->inventory.items[i].type == ITEM_TYPE_PICKAXE) {
            ItemDataPickaxe *data = p->inventory.items[i].item_data.pickaxe_data;
            if (data->type > bestPickaxe) {
                bestPickaxe = data->type;
            }
        }

        foundSlots += 1;
    }

    if (bestPickaxe == PICKAXE_TYPE_NULL) {
        return (ActivityResult){ACTIVITY_FAILED_NO_PICKAXE};
    }

    // TODO: Do the mining activity

    return (ActivityResult){ACTIVITY_FAILED};
}
