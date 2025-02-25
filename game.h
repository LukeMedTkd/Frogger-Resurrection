#include <stdlib.h>
#include <ncurses.h>
#include "struct.h"

// GAME VARIABLES
#define MANCHES 5
#define SCORE 0
#define TIME 60
#define LIFES (MANCHES)
#define N_MAX_BULLETS 3
#define N_DENS 5
#define N_STREAM 8
#define MAX_N_CROCODILE_PER_STREAM 3

// Entities
#define N_ENTITIES (MAX_N_CROCODILE_PER_STREAM * N_STREAM + 2)
#define N_BULLETS N_ENTITIES

// Streams
#define STREAM_DIRECTION ((rand() % 2) * 2 - 1) // Return 1 or -1
#define INVERT_DIRECTION -1
#define MAX_STREAM_SPEED 100000
#define MIN_STREAM_SPEED 40000

// Outcomes
#define NO_OUTCOME -1
#define WINNER_OUTCOME 22
#define LOSER_OUTCOME 21
#define TIME_IS_UP_OUTCOME 20

// Functions Prototypes
Game_var initialize_gameVar();
void randomize_streams_speed(int *stream_speed);
void randomize_streams_direction(int *stream_speed);
void set_crocodiles_on_streams(Character *Entities, int *fds, Game_var *gameVar);
int get_nStream_based_on_id(int id);
void outcome(WINDOW *game, Game_var *gameVar);
void start_game(WINDOW *score, WINDOW *game);