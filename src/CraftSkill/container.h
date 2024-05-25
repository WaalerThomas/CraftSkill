#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <stdlib.h>
#include <stdint.h>

#include "item.h"

#define MAX_CONTAINER_CAPACITY 10000

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
char* container_get_item_name(Container *c, uint16_t index);
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
