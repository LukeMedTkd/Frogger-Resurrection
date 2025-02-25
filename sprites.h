#include <ncurses.h>
#include "struct.h"

extern bool crocodiles_creation;

// Frog constants
#define FROG_DIM_X 10
#define FROG_DIM_Y 4

// Crocodile constants
#define CROCODILE_DIM_X 30
#define CROCODILE_DIM_Y 4

// Dens constants
#define DENS1_START 20
#define DENS2_START 45
#define DENS3_START 70
#define DENS4_START 95
#define DENS5_START 120

// Animation's OUTCOME Duration
#define DURATION 3200000

// DEMO constants
#define DURATION_MAX 50000 
#define DURATION_MIN 5000
#define DEMO_DURATION 145000

// Functions Prototypes
void print_timer(WINDOW *score, int timer);
void print_score(WINDOW *score, int vscore);
void print_lifes(WINDOW *score, int lifes);
void print_game_area(WINDOW *game, bool *dens);
void print_frog(WINDOW *game, Character frog_entity);
void print_frog_bullets(WINDOW *game, Character *Bullets);
void print_crocodiles(WINDOW *game, Character *Entities, int *stream_speed_with_dir);
void print_crocodiles_bullets(WINDOW *game, Character *Bullets);
void print_lost_game(WINDOW *game);
void print_time_is_up(WINDOW *game);
void print_won_game(WINDOW *game);
void print_demo(WINDOW *menu);
void draw_von_neumann_machine(WINDOW *menu);