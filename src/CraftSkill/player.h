#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdint.h>

#include "container.h"

typedef struct {
    uint16_t health;
    uint16_t max_health;
    Container inventory;
    Equipped equipped;
} Player;

Player player_alloc(uint16_t max_health);
void player_cleanup(Player *p);
void player_equip(Player *p, Container *c, const char *item_name);
void print_player_stats(Player *p);

#endif // PLAYER_H_
