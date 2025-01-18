# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Libraries
LIBS = -lncursesw

# Source files and target
SRC = main.c game.c process.c entity.c sprites.c utils.c
OBJ = ${SRC:.c=.o}
TARGET = output

# Default target
all: ${TARGET}

# Link the target
${TARGET}: ${OBJ}
	${CC} ${CFLAGS} -o $@ $^ ${LIBS}

# Compile each .c file into .o
%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

# Clean up build files
clean:
	rm -f ${TARGET} ${OBJ}

# Debug build
debug: CFLAGS += -g
debug: clean ${TARGET}
