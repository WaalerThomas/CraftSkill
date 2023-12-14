#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "CraftSkill/game.h"
#include "CraftSkill/player.h"
#include "CraftSkill/container.h"
#include "CraftSkill/userinput.h"

void print_message(const char *message, va_list args)
{
    vprintf(message, args);
    printf("\n");
}

int main(void)
{
    Game game = game_new();

    event_subscribe(&game.eventHandler, "event_print", print_message);

    // Create some random items and add them to the inventory
    Item axe = item_new("Axe", ITEM_TYPE_WEAPON, 1);
    Item stick = item_new("Stick", ITEM_TYPE_DEFAULT, 5);
    stick.count = 3;
    Item ball = item_new("Ball", ITEM_TYPE_DEFAULT, 1);
    container_add(&game.player.inventory, &axe);
    container_add(&game.player.inventory, &stick);
    container_add(&game.player.inventory, &ball);

    print_player_stats(&game.player);
    print_container_content(&game.player.inventory);

    player_equip(&game.player, &game.player.inventory, "Axe");
    container_remove(&game.player.inventory, "Stick", 2);
    print_player_stats(&game.player);
    print_container_content(&game.player.inventory);

    // Main game loop
    while (game.isRunning) {
        userinput_read(&game.userInput);
        parse_commands(&game);
    }

    // Perform cleanup
    game_cleanup(&game);
    return 0;
}
