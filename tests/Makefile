CC			= gcc
CFLAGS		= -mmacosx-version-min=12.6
INCLUDES 	= -I../src -I../vendors/cunit/CUnit
LDFLAGS		= -L../

.PHONY:test-container test-player

all:

test: test-container test-player
	./test-container
	./test-player
	@echo OK!

test-container: test-container.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -lcraftskill -lcunit $^ -o $@
	rm -f $@.o

test-player: test-player.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -lcraftskill -lcunit $^ -o $@
	rm -f $@.o
