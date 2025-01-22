#include <stdlib.h>
#include <ncurses.h>

#define MANCHES 5
#define SCORE 0
#define TIME 60000
#define N_STREAM 8
#define MAX_N_CROCODILE_PER_STREAM 3
#define N_ENTITIES (MAX_N_CROCODILE_PER_STREAM * N_STREAM + 2)

// STREAMS
#define STREAM_DIRECTION ((rand() % 2) * 2 - 1) // Return 1 or -1
#define INVERT_DIRECTION -1
#define MAX_STREAM_SPEED 150000
#define MIN_STREAM_SPEED 30000
#define MAX_SPAWN_TIME 700000
#define MIN_SPAWN_TIME 100000

// Functions Prototypes
void start_game(WINDOW *score, WINDOW *game);