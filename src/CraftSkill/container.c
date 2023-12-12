#include "container.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

Item item_new(char *name, ItemType item_type, size_t max_amount)
{
    Item i;
    i.name = name;
    i.count = 1;
    i.max_amount = (max_amount == 0) ? 1 : max_amount;
    i.type = item_type;

    return i;
}

Container container_alloc(char *name, size_t capacity)
{
    Container c;
    c.name = name;

    if (capacity == 0)
        c.capacity = 1;
    else if (capacity > 10000)
        c.capacity = 10000;
    else
        c.capacity = capacity;

    c.count = 0;
    c.items = calloc(c.capacity, sizeof(Item));

    return c;
}

void container_cleanup(Container *c)
{
    free(c->items);
}

void container_add(Container *c, Item *i)
{
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

void container_remove(Container *c, const char *name, size_t count)
{
    int32_t item_index = container_get_item_index(c, name);
    if (item_index == -1) {
        fprintf(stderr, "ERROR: Could not find item %s in container %s\n", name, c->name);
        return;
    }

    size_t current_count = c->items[item_index].count;
    if (current_count - count == 0) {
        c->items[item_index].count = 0;
        c->count -= 1;
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
    for (size_t i = 0; i < c->count; i++) {
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
