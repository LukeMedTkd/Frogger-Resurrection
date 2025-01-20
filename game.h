#include <ncurses.h>
#include "entity.h"

#define MANCHES 5
#define SCORE 0
#define TIME 60000 //msleep(milliseconds)
#define N_STREAM 8
#define MAX_N_CROCODILE_PER_STREAM 3
#define N_ENTITIES (MAX_N_CROCODILE_PER_STREAM * N_STREAM + 2)

// Functions Prototypes
void start_game(WINDOW *score, WINDOW *game);