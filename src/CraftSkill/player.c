#include "player.h"
#include "container.h"

#include <stdio.h>
#include <string.h>

Player player_alloc(uint16_t max_health)
{
    Player p;
    p.max_health = (max_health == 0) ? 1 : max_health;
    p.health = p.max_health;
    p.inventory = container_alloc("Inventory", 28);
    p.equipped = (Equipped){0};

    return p;
}

void player_cleanup(Player *p)
{
    container_cleanup(&p->inventory);
    equipped_cleanup(&p->equipped);
}

void player_equip(Player *p, Container *c, const char *item_name)
{
    // Find the index of the item in the container
    int32_t item_index = container_get_item_index(c, item_name);
    if (item_index == -1) {
        fprintf(stderr, "ERROR: Could not find the item %s in the container %s\n", item_name, c->name);
        return;
    }

    // Figure out which equipment slot to put the item
    Item *item = &c->items[item_index];
    Item *equip_slot = equipped_get_slot(&p->equipped, item->type);
    if (equip_slot == NULL) {
        fprintf(stderr, "ERROR: Didn't find an equipment slot for item %s type %d\n", item_name, item->type);
        return;
    }

    // Check whether the slot is empty or not
    // TODO: Switch the items instead of failing
    if (equip_slot->count > 0) {
        fprintf(stderr, "ERROR: Could not equip %s, slot is not empty\n", item_name);
        return;
    }

    // Move the item info into the equipment slot
    *equip_slot = *item;
    container_remove(c, item_name, 1);
}

void print_player_stats(Player *p)
{
    printf("===== Player Stats =====\n");
    printf("Health: \t%3d / %3d\n", p->health, p->max_health);

    char *main_name = p->equipped.mainhand.name;
    char *off_name = p->equipped.offhand.name;
    if (p->equipped.mainhand.count == 0) main_name = "Empty";
    if (p->equipped.offhand.count == 0)  off_name = "Empty";

    printf("Mainhand: %s\nOffhand: %s\n", main_name, off_name);
    print_container(&p->inventory);
    printf("========================\n");
}

void print_player_skills(Player *p)
{
    (void) p;
    printf("NOT IMPLEMENTED printing skills\n");
}
