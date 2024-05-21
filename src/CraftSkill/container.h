#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <stdlib.h>
#include <stdint.h>

#define MAX_CONTAINER_CAPACITY 10000

typedef enum {
    ITEM_TYPE_DEFAULT = 0,
    ITEM_TYPE_WEAPON,
    ITEM_TYPE_TOOL,
    ITEM_TYPE_HELMET,
    ITEM_TYPE_TORSO,
    ITEM_TYPE_LEGGINGS,
    ITEM_TYPE_SHOES,
    ITEM_TYPE_GLOVES,
    ITEM_TYPE_RING,
    ITEM_TYPE_NECKLASE,
    ITEM_TYPE_CAPE,
    ITEM_TYPE_COUNT
} ItemType;

typedef struct {
    int8_t stab;
} ItemDataWeapon;

typedef union {
    ItemDataWeapon *weapon_data;
} ItemData;

typedef struct {
    ItemType type;
    ItemData item_data;

    char *name;
    size_t count;
    size_t max_amount;
} Item;

Item item_new(char *name, size_t max_amount);
Item item_new_weapon(char *name);

typedef struct {
    char *name;
    Item *items;
    size_t count;
    size_t capacity;
} Container;

Container container_alloc(char *name, size_t capacity);
void container_cleanup(Container *c);
void container_add(Container *c, Item *i);
void container_add_list(Container *c, Item *items, size_t count);
void container_remove(Container *c, const char *name, size_t count);
int32_t container_get_item_index(Container *c, const char *name);
void print_container(Container *c);
void print_container_content(Container *c);

typedef struct {
    Item mainhand;
    Item offhand;
    Item hands;
    Item head;
    Item torso;
    Item legs;
    Item feet;
    Item back;
    Item neck;
    Item finger;
} Equipped;

void equipped_cleanup(Equipped *e);
Item* equipped_get_slot(Equipped *e, ItemType item_type);

#endif // CONTAINER_H_
