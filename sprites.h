#include <ncurses.h>
#include "struct.h"

// Frog constants
#define FROG_DIM_X 10
#define FROG_DIM_Y 4

// Crocodile constants
#define CROCODILE_DIM_X 30
#define CROCODILE_DIM_Y 4

// Functions Prototypes
void print_game_area(WINDOW *game);
void print_frog(WINDOW *game, Character frog_entity);