#ifndef ACTIVITIES_H_
#define ACTIVITIES_H_

#include <stdint.h>

#include "player.h"

typedef enum {
    ACTIVITY_OK,
    ACTIVITY_FAILED,
    ACTIVITY_FAILED_LOW_LEVEL,
    ACTIVITY_FAILED_NO_PICKAXE
} ActivityReturnCode;

typedef struct {
    ActivityReturnCode code;
} ActivityResult;

typedef struct {
    char *name;
    uint8_t level_required;
} Mineable;

ActivityResult activity_mine(Player *p, Mineable m);

#endif // ACTIVITIES_H_
