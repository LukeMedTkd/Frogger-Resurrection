#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include "struct.h"

#define MANCHES 3
#define SCORE 0
#define TIME 60
#define LIFES MANCHES
#define N_DENS 5
#define N_STREAM 8
#define MAX_N_CROCODILE_PER_STREAM 3
#define N_ENTITIES (MAX_N_CROCODILE_PER_STREAM * N_STREAM + 2)

// STREAMS
#define STREAM_DIRECTION ((rand() % 2) * 2 - 1) // Return 1 or -1
#define INVERT_DIRECTION -1
#define MAX_STREAM_SPEED 100000
#define MIN_STREAM_SPEED 30000
#define MAX_SPAWN_TIME 6000000
#define MIN_SPAWN_TIME 3000000

// OUTCOMES
#define WINNER_OUTCOME 22
#define LOSER_OUTCOME 21
#define TIME_IS_UP_OUTCOME 20

// Functions Prototypes
void randomize_streams_speed(int *streams_speed);
void randomize_streams_direction(int *stream_speed);
void set_crocodiles_on_streams(Character *Entities, int *fds, Game_var *gameVar);
int get_nStream_based_on_id(int id);
void outcome(WINDOW *game, Game_var *gameVar);
void start_game(WINDOW *score, WINDOW *game);