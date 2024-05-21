#include "game.h"
#include "container.h"
#include "player.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Forward decleration
void command_info(Game *g);

void print_something(const char *message, va_list args)
{
    (void) message;
    (void) args;
    printf("Hello, this is just some random text printed. Called from event handler\n");
}

void print_other(const char *message, va_list args)
{
    (void) message;
    (void) args;
    printf("This is the next function added to the same even key\n");
}

Game game_new()
{
    Game g;
    g.player = player_alloc(10);
    g.userInput = userinput_alloc();
    g.eventHandler = eventhandler_alloc();

    event_subscribe(&g.eventHandler, "test_event", print_something);
    event_subscribe(&g.eventHandler, "test_event", print_other);

    g.isRunning = true;
    return g;
}

void game_cleanup(Game *game)
{
    player_cleanup(&game->player);
    userinput_cleanup(&game->userInput);
    eventhandler_cleanup(&game->eventHandler);
}

void command_container(Game *g)
{
    // Check the next tokens for accepted verbs
    // Check if it has more tokens
    if (g->userInput.token_count == 1) {
        // TODO: Print the available commands for container
        event_emit(&g->eventHandler, "event_print", "TODO: Print the available commands for container");
        return;
    }

    char *sc = g->userInput.tokens[1];
    if (strcmp(sc, "list") == 0 || strcmp(sc, "l") == 0) {
        printf("TODO: Print all available containers\n");
        return;
    }

    char *container = g->userInput.tokens[1];

    if (g->userInput.token_count == 2) {
        printf("TODO: Print container info\n");
        return;
    }
}

static void command_player_print()
{
    // TODO: Print the available commands for player
    printf("NOT IMPLEMENTED printing the available commands for player!\n");
}

void command_player(Game *g)
{
    // Check the next tokens for accepted verbs
    // Check if it has more tokens
    if (g->userInput.token_count == 1) {
        command_player_print();
        return;
    }

    char *sc = g->userInput.tokens[1];
    if (strcmp(sc, "list") == 0 || strcmp(sc, "l") == 0) {
        if (g->userInput.token_count == 2) {
            print_player_stats(&g->player);
            return;
        }

        sc = g->userInput.tokens[2];
        if (strcmp(sc, "stats") == 0) {
            print_player_stats(&g->player);
            return;
        }
        if (strcmp(sc, "inventory") == 0 || strcmp(sc, "inv") == 0) {
            print_container_content(&g->player.inventory);
            return;
        }
        if (strcmp(sc, "skills") == 0) {
            print_player_skills(&g->player);
            return;
        }

        command_player_print();
        return;
    }
    if (strcmp(sc, "equip") == 0) {
        if (g->userInput.token_count < 3) {
            command_player_print();
            return;
        }

        // TODO: Be able to equip from slot number
        // TODO: Give feadback from equipping the item
        char *itemName = g->userInput.tokens[2];
        sc = g->userInput.tokens[3];
        player_equip(&g->player, &g->player.inventory, itemName);
        return;
    }

    command_player_print();
}

void parse_commands(Game *g)
{
    // Why not make a switch?
    char *command = g->userInput.tokens[0];

    if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0) {
        event_emit(&g->eventHandler, "event_print", "Exiting the game");
        g->isRunning = false;
    }
    else if (strcmp(command, "test") == 0) {
        event_emit(&g->eventHandler, "test_event", NULL);
    }
    else if (strcmp(command, "help") == 0) {
        event_emit(&g->eventHandler, "event_print", "NOT IMPLEMENTED!");
    }
    else if (strcmp(command, "info") == 0) {
        command_info(g);
    }
    else if (strcmp(command, "container") == 0) {
        command_container(g);
    }
    else if (strcmp(command, "player") == 0) {
        command_player(g);
    }
    else {
        event_emit(&g->eventHandler, "event_print", "Unknown command '%s'", command);
    }
}

void command_info(Game *g)
{
    event_emit(&g->eventHandler, "event_print", "Inside command_info, %d", g->userInput.token_count);
}
