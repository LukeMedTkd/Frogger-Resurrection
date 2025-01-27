#include <ncurses.h>
#include "struct.h"

// Frog constants
#define FROG_DIM_X 10
#define FROG_DIM_Y 4

// Crocodile constants
#define CROCODILE_DIM_X 30
#define CROCODILE_DIM_Y 4


// Dens costants
#define DENS1_START 20
#define DENS2_START 45
#define DENS3_START 70
#define DENS4_START 95
#define DENS5_START 120

// Functions Prototypes
void print_timer(WINDOW *score, int timer);
void print_game_area(WINDOW *game, bool *dens);
void print_frog(WINDOW *game, Character frog_entity);
void print_crocodiles(WINDOW *game, Character *Entities, int *stream_speed_with_dir);