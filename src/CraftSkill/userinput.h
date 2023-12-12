#ifndef USERINPUT_H
#define USERINPUT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    size_t buffer_size;
    char *buffer;
    char *pch;
    size_t token_max;
    char **tokens;
    size_t token_count;
} UserInput;

UserInput userinput_alloc();
void userinput_cleanup(UserInput *ui);
void userinput_read(UserInput *ui);

#endif // USERINPUT_H
