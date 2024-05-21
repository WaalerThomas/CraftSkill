#include "container.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

Item item_new(char *name, size_t max_amount)
{
    Item i = {0};
    i.name = name;
    i.count = 1;
    i.max_amount = (max_amount == 0) ? 1 : max_amount;
    i.type = ITEM_TYPE_DEFAULT;

    return i;
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

static void item_cleanup(Item *i)
{
    switch (i->type) {
        case ITEM_TYPE_DEFAULT:
            break;
        case ITEM_TYPE_WEAPON:
            free(i->item_data.weapon_data);
            break;
        case ITEM_TYPE_TOOL:
            break;
        case ITEM_TYPE_HELMET:
            break;
        case ITEM_TYPE_TORSO:
            break;
        case ITEM_TYPE_LEGGINGS:
            break;
        case ITEM_TYPE_SHOES:
            break;
        case ITEM_TYPE_GLOVES:
            break;
        case ITEM_TYPE_RING:
            break;
        case ITEM_TYPE_NECKLASE:
            break;
        case ITEM_TYPE_CAPE:
            break;
        default:
            break;
    }
}

Container container_alloc(char *name, size_t capacity)
{
    Container c;
    c.name = name;

    if (capacity == 0)
        c.capacity = 1;
    else if (capacity > MAX_CONTAINER_CAPACITY)
        c.capacity = MAX_CONTAINER_CAPACITY;
    else
        c.capacity = capacity;

    c.count = 0;
    c.items = calloc(c.capacity, sizeof(Item));

    return c;
}

void container_cleanup(Container *c)
{
    uint16_t foundSlots = 0;
    for (size_t i = 0; i < c->capacity; i++) {
        if (foundSlots == c->count) {
            break;
        }
        if (c->items[i].count == 0) {
            continue;
        }

       item_cleanup(&c->items[i]);
    }
    free(c->items);
}

void container_add(Container *c, Item *i)
{
    // TODO: Check if item already exists in container
    if (c->count + 1 > c->capacity) {
        fprintf(stderr, "ERROR: Can not add item. Container is full\n");
        return;
    }
    c->items[c->count] = *i;
    c->count += 1;
}

void container_add_list(Container *c, Item *items, size_t count)
{
    (void) c;
    (void) items;
    (void) count;
    assert(0);
}

static void container_reorder(Container *c)
{
    size_t leftIndex = 0;
    size_t rightIndex = 1;
    size_t moved = 0;

    while (c->count > moved) {
        if (c->items[leftIndex].count > 0) {
            moved++;
            leftIndex++;
            if (leftIndex > c->capacity) {
                printf("FATAL: Reorder Left Index bigger than container capacity\n");
                return;
            }
            rightIndex++;
            if (rightIndex > c->capacity) {
                printf("FATAL: Reorder Right Index bigger than container capacity\n");
                return;
            }

            continue;
        }

        if (c->items[rightIndex].count == 0) {
            rightIndex++;
            if (rightIndex > c->capacity) {
                printf("FATAL: Reorder Right Index bigger than container capacity\n");
                return;
            }

            continue;
        }

        // Move the right into left
        Item temp = c->items[leftIndex];
        c->items[leftIndex] = c->items[rightIndex];
        c->items[rightIndex] = temp;
    }
}

void container_remove(Container *c, const char *name, size_t count)
{
    int32_t item_index = container_get_item_index(c, name);
    if (item_index == -1) {
        fprintf(stderr, "ERROR: Could not find item %s in container %s\n", name, c->name);
        return;
    }

    size_t current_count = c->items[item_index].count;
    if (current_count - count == 0) {
        c->items[item_index] = (Item){0};
        c->count -= 1;
        /* container_reorder(c); */
        return;
    }
    if (count > current_count) {
        fprintf(stderr, "ERROR: Can not remove more items than is available(%zu), %zu\n", current_count, count);
        return;
    }

    c->items[item_index].count -= count;
}

int32_t container_get_item_index(Container *c, const char *name)
{
    int32_t item_index = -1;
    uint16_t foundSlots = 0;
    for (size_t i = 0; i < c->count; i++) {
        if (foundSlots == c->count) {
            break;
        }
        if (c->items[i].count == 0) {
            continue;
        }

        if (strcmp(c->items[i].name, name) == 0) {
            item_index = i;
            break;
        }
    }

    return item_index;
}

void print_container(Container *c)
{
    printf("%s:  %3zu / %3zu\n", c->name, c->count, c->capacity);
}

void print_container_content(Container *c)
{
    printf("---------------------------------------------------\n");
    printf("Container - '%s':\n", c->name);
    printf("Slotnr.     Item name          Amount     Type\n");
    uint16_t foundSlots = 0;
    for (size_t i = 0; i < c->capacity; i++) {
        if (foundSlots == c->count) {
            break;
        }
        if (c->items[i].count == 0) {
            continue;
        }

        char *type_str;
        ItemType type = c->items[i].type;
        switch (type) {
            case ITEM_TYPE_DEFAULT: type_str = "Default"; break;
            case ITEM_TYPE_WEAPON: type_str = "Weapon"; break;
            case ITEM_TYPE_TOOL: type_str = "Tool"; break;
            default: type_str = "Not Reachable";
        }

        printf("%-11zu %-18s %-10zu %s\n", (i + 1), c->items[i].name, c->items[i].count, type_str);
        foundSlots += 1;
    }
    printf("---------------------------------------------------\n");
}

void equipped_cleanup(Equipped *e)
{
    item_cleanup(&e->mainhand);
    e->mainhand = (Item){0};
    item_cleanup(&e->offhand);
    e->offhand = (Item){0};
    item_cleanup(&e->hands);
    e->hands = (Item){0};
    item_cleanup(&e->head);
    e->head = (Item){0};
    item_cleanup(&e->torso);
    e->torso = (Item){0};
    item_cleanup(&e->legs);
    e->legs = (Item){0};
    item_cleanup(&e->feet);
    e->feet = (Item){0};
    item_cleanup(&e->back);
    e->back = (Item){0};
    item_cleanup(&e->neck);
    e->neck = (Item){0};
    item_cleanup(&e->finger);
    e->finger = (Item){0};
}

Item* equipped_get_slot(Equipped *e, ItemType item_type)
{
    if (item_type == ITEM_TYPE_DEFAULT || item_type == ITEM_TYPE_COUNT) {
        return NULL;
    }

    if (item_type == ITEM_TYPE_TOOL || item_type == ITEM_TYPE_WEAPON) {
        return &e->mainhand;
    }

    return NULL;
}
