#include <unistd.h>
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
#define FROG_MOVE_X 1
#define FROG_INIT_Y (GAME_HEIGHT - FROG_DIM_Y)
#define FROG_INIT_X ((GAME_WIDTH / 2) - (FROG_DIM_X / 2))
#define FROG_POSITION_SIG 0
#define FROG_SHOT_SIG 1

// Crocodile constants
#define FIRST_CROCODILLE 2
#define LAST_CROCODILLE 26
#define CROCODILE_MOVE_X 1
#define CROCODILE_OFFSET_Y (DENS_HEIGTH + GRASS_HEIGHT)
#define CROCODILE_ONLINE 1
#define CROCODILE_OFFLINE 0

#define TIME_ID 1

// Functions Prototypes
void frog_process(int pipe_write, int* params);
void reset_frog_position(Character *frog_entity);
void crocodile_process(int pipe_write, int* args);
void reset_crocodile_position(Character *crocodile_entity, int* args);
void time_process(int pipe_write, int* params);
void parent_process(WINDOW *game, WINDOW *score, int pipe_read, Character *Entities, Game_var gameVar);