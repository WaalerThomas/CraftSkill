#include "game.h"

#include <string.h>

void print_something(const char *message, ...)
{
    (void) message;
    printf("Hello, this is just some random text printed. Called from event handler\n");
}

void print_other(const char *message, ...)
{
    (void) message;
    printf("This is the next function added to the same even key\n");
}

Game game_new()
{
    Game g;
    g.player = player_new(10);
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

void parse_commands(Game *g)
{
    char *command = g->userInput.tokens[0];

    if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0) {
        printf("Exiting the game\n");
        g->isRunning = false;
    }
    else if (strcmp(command, "test") == 0) {
        printf("Running event_emit() on event 'test_event' ...\n");
        event_emit(&g->eventHandler, "test_event", NULL);
        event_emit(&g->eventHandler, "event_print", "This is some printing message argument thing");
    }
    else {
        printf("Unknown command '%s'\n", command);
    }
}
