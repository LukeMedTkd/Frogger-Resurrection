#include <ncurses.h>
#include "struct.h"

// Frog constants
#define FROG_DIM_X 6
#define FROG_DIM_Y 3

// Crocodile constants
#define CROCODILE_DIM_X 20
#define CROCODILE_DIM_Y 4

// Functions Prototypes
void print_game_area(WINDOW *game);
void print_frog(WINDOW *game, Character frog_entity);