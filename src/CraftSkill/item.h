#ifndef ITEM_H_
#define ITEM_H_

#include <stdint.h>
#include <stddef.h>

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
    ITEM_TYPE_PICKAXE,
    ITEM_TYPE_COUNT
} ItemType;

typedef enum {
    PICKAXE_TYPE_NULL = -1,
    PICKAXE_TYPE_BRONZE,
    PICKAXE_TYPE_IRON,
    PICKAXE_TYPE_STEEL,
    PICKAXE_TYPE_BLACK,
    PICKAXE_TYPE_MITHRIL,
    PICKAXE_TYPE_ADAMANT,
    PICKAXE_TYPE_RUNE,
    PICKAXE_TYPE_DRAGON,
    PICKAXE_TYPE_COUNT
} PickaxeType;

typedef struct {
    int8_t stab;
} ItemDataWeapon;

typedef struct {
    PickaxeType type;
} ItemDataPickaxe;

typedef union {
    ItemDataWeapon *weapon_data;
    ItemDataPickaxe *pickaxe_data;
} ItemData;

typedef struct {
    ItemType type;
    ItemData item_data;

    char *name;
    size_t count;
    size_t max_amount;
    char *examine_text;
} Item;

Item item_new(char *name, size_t max_amount);
Item item_new_weapon(char *name);
Item item_new_pickaxe(char *name, PickaxeType type);
void item_cleanup(Item *i);
char* item_type(Item *i);

#endif // ITEM_H_
