TARGET		= libcraftskill.a

SRC			= $(wildcard src/CraftSkill/*.c)
OBJ			= $(SRC:.c=.o)

INCLUDES	= -I./src

LIB			=

CC			= gcc -std=c17
CFLAGS		= -Wall -Wextra -Werror -pedantic -g

.SUFFIXES: .c

# Specify how to compile the .c files
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(TARGET) craftskill clean

craftskill: $(OBJ)
	$(CC) $(CFLAGS) -o craftskill src/craftskill.c $(INCLUDES) -L. -lcraftskill

$(TARGET): $(OBJ)
	ar rcs $(TARGET) $(OBJ)

clean:
	rm -f $(OBJ)

test: $(TARGET)
	cd tests/; make test; cd ..; make clean
