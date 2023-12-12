#ifndef GAME_H_
#define GAME_H_

#include <stdbool.h>

#include "player.h"
#include "userinput.h"
#include "eventhandler.h"

typedef struct {
    Player player;
    UserInput userInput;
    EventHandler eventHandler;

    bool isRunning;
} Game;

Game game_new();
void game_cleanup();

void parse_commands(Game *g);

#endif // GAME_H_
