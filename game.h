#include <stdlib.h>
#include <ncurses.h>

#define MANCHES 5
#define SCORE 0
#define TIME 60
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

// Functions Prototypes
void randomize_streams_speed(int *streams_speed);
void randomize_streams_direction(int *stream_speed);
void randomize_spawn_time(int *stream_speed, int *spawn_time);
void start_game(WINDOW *score, WINDOW *game);