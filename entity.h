#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include "process.h"
#include "utils.h"
#include "sprites.h"

#define TRUE 1
#define FALSE 0 

// Frog constants
#define FROG_ID 0
#define FROG_MOVE_Y FROG_DIM_Y
#define FROG_MOVE_X FROG_DIM_X
#define FROG_INIT_Y (GAME_HEIGHT - FROG_DIM_Y)
#define FROG_INIT_X ((COLS / 2) - (FROG_DIM_X / 2))
#define FROG_POSITION_SIG 0
#define FROG_SHOT_SIG 1

// Crocodile constants
#define CROCODILE_OFFSET_Y (SCORE_HEIGHT + GRASS_HEIGHT)


// Functions Prototypes
void frog_process(int pipe_write, int* params);
void reset_frog_position(Character *frog_entity);
void crocodile_process(int pipe_write, int* params);
void reset_crocodile_position(Character *crocodile_entity, int* args);
void parent_process(WINDOW *game, int pipe_read, Character *Entities);