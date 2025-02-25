#include <unistd.h>
#include "process.h"
#include "utils.h"
#include "sprites.h"
#include <sys/select.h>

#define TRUE 1
#define FALSE 0 

// Sosket Costants
#define SOCKET_PATH "/tmp/mysocket"

// Frog constants
#define FROG_ID 0
#define FROG_MOVE_Y FROG_DIM_Y
#define FROG_MOVE_X 1
#define FROG_INIT_Y (GAME_HEIGHT - FROG_DIM_Y)
#define FROG_INIT_X ((GAME_WIDTH / 2) - (FROG_DIM_X / 2))
#define FROG_POSITION_SIG 0
#define FROG_SHOT_SIG 1
#define KEY_SHOT 32

// Crocodile constants
#define FIRST_CROCODILE 2
#define LAST_CROCODILE (FIRST_CROCODILE + (N_STREAM * MAX_N_CROCODILE_PER_STREAM))
#define CROCODILE_MOVE_X 1
#define CROCODILE_OFFSET_Y (DENS_HEIGTH + GRASS_HEIGHT)
#define CROCODILE_ONLINE 1
#define CROCODILE_OFFLINE 0
#define MAX_RANDOM_SHOT 200
#define MIN_RANDOM_SHOT 1

// FROG Bullets constants
#define LEFT_FROG_BULLET_ID 50
#define RIGHT_FROG_BULLET_ID 51
#define FROG_BULLET_SPEED 12000

// CROCODILE Bullets constants
#define BULLET_OFFSET_ID 50
#define MAX_BULLET_SPEED_INCREASE 60
#define MIN_BULLET_SPEED_INCREASE 45
#define MAX_BULLET_SPAWN 150000
#define MIN_BULLET_SPAWN 100000
#define ACTIVE 1
#define DEACTIVE 0

// Time constants
#define TIME_ID 1

// Functions Prototypes
void frog_process(int pipe_write, int* args);
void reset_frog_position(Character *frog_entity);
void left_frog_bullet_process(int pipe_write, int* args);
void right_frog_bullet_process(int pipe_write, int* args);
void reset_frog_bullet_position(Character *Entities, Character *Bullets);
void crocodile_process(int pipe_write, int* args);
void reset_crocodile_position(Character *crocodile_entity, int n_stream, Game_var *gameVar);
void reset_crocodile_bullet_position(Character *Entities, Character *Bullets, Game_var *gameVar, int index);
void reset_timer(Game_var *gameVar);
void timer_process(int pipe_write, int* args);
void parent_process(WINDOW *game, WINDOW *score, int *fds, int server_fd, Character *Entities, Character *Bullets, Game_var *gameVar);