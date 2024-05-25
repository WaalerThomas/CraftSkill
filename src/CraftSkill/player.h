#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdint.h>

#include "container.h"

typedef struct {
    char *name;
    uint8_t level;
    uint32_t current_xp;
} Skill;

typedef struct {
    Skill mining;
} Skills;

typedef struct {
    uint16_t health;
    uint16_t max_health;
    Container inventory;
    Equipped equipped;
    Skills skills;
} Player;

Player player_alloc(uint16_t max_health);
void player_cleanup(Player *p);
void player_equip(Player *p, Container *c, int32_t item_index);
void player_equip_name(Player *p, Container *c, const char *item_name);
void print_player_stats(Player *p);
void print_player_skills(Player *p);

#endif // PLAYER_H_
