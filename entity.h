#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>

#define TRUE 1
#define FALSE 0 

// Frog constants
#define FROG_ID 0
#define FROG_DIM_X 3
#define FROG_DIM_Y 4

#define FROG_MOVE_Y FROG_DIM_Y
#define FROG_MOVE_X FROG_DIM_X
// #define FROG_INIT_Y LINE_BANK_2
// #define FROG_INIT_X (MAIN_COLS/2-FROG_DIM_X/2)
// #define FROG_LIM_UP LINE_HOLES
// #define FROG_LIM_DOWN LINE_BANK_2
// #define FROG_LIM_LEFT 0
// #define FROG_LIM_RIGHT (MAIN_COLS-FROG_DIM_X)
// #define FROG_NOT_ON_CROCCODILE (-1)
// #define FROG_POSITION_SIG 0
#define FROG_SHOT_SIG 1

//void Frog(int pipe_fds, item entity,WINDOW *game, int running);