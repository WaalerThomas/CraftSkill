#include "userinput.h"

UserInput userinput_alloc()
{
    UserInput ui;
    ui.buffer_size = 150;
    ui.buffer = malloc(sizeof(char) * ui.buffer_size);
    ui.pch = NULL;

    ui.token_max = 25;
    ui.token_count = 0;
    ui.tokens = malloc(sizeof(char*) * ui.token_max);
    return ui;
}

void userinput_cleanup(UserInput *ui)
{
    free(ui->buffer);
    free(ui->tokens);
}

void userinput_read(UserInput *ui)
{
    printf("> ");
    /* getline(&ui->buffer, &ui->buffer_size, stdin); */
    fgets(ui->buffer, ui->buffer_size, stdin);
    ui->buffer[strcspn(ui->buffer, "\n")] = 0;

    ui->token_count = 0;
    ui->pch = strtok(ui->buffer, " ");
    while (ui->pch != NULL) {
        if (ui->token_count + 1 > ui->token_max) {
            fprintf(stderr, "ERROR: Too many tokens given. Max is %zu\n", ui->token_max);
            break;
        }

        ui->tokens[ui->token_count] = ui->pch;
        ui->token_count += 1;
        ui->pch = strtok(NULL, " ");
    }
}
