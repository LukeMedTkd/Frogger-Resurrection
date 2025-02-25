# main = game.h utils.h sprites.h sound.h
# game = game.h entity.h sprites.h struct.h utils.h sprites.h sound.h collisions.h
# struct = struct.h miniaudio.h
# utils = utils.h design.h

# game.o: game.c ${game}
#     ${CC} -c $*.c -o $@ ${CFLAGS} ${LIBS}

# main.o: main.c ${main}
#     ${CC} -c $*.c -o $@ ${CFLAGS} ${LIBS}

# utils.o: utils.c ${utils}
#     ${CC} -c $*.c -o $@ ${CFLAGS} ${LIBS}



# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-parameter -Wno-misleading-indentation

# Libraries
LIBS = -lncursesw -lm

SRC = $(wildcard *.c) # compile all .c files in the directory
HEADERS = $(wildcard *.h)
TARGET = frogger-resurrection

all:$(TARGET)

# Build the target
$(TARGET):$(SRC) $(HEADERS)
	$(CC) -o $(TARGET) $(SRC) $(LIBS) $(CFLAGS)

# Clean up build files
clean:
	rm -f frogger-resurrection