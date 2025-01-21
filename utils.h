// Include Lib
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <locale.h>
#include "sprites.h"
#include "game.h"

#define DEBUG_FILE_NAME "log.txt"

// Defined Color_Id
#define COLOR_FROG 100
#define COLOR_LEGS 102
#define COLOR_RIVER 110
#define COLOR_CROCODILLE 120
#define COLOR_DENS 130
#define COLOR_GRASS 140
#define COLOR_SCORE 150

// Defined Color_Pair_Id
#define COLOR_FROG_ID 200
#define COLOR_EYE_ID 101
#define COLOR_LEGS_ID 102
#define COLOR_RIVER_ID 210
#define COLOR_CROCODILLE_ID 220
#define COLOR_DENS_ID 230
#define COLOR_GRASS_ID 240
#define COLOR_SCORE_ID 250


// Defined sizes of game area
#define DENS_HEIGTH 5
#define DENS_Y_START 0
#define DENS_Y_END (DENS_Y_START+DENS_HEIGTH)

#define SCORE_HEIGHT 1
#define GAME_HEIGHT ((FROG_DIM_Y * N_STREAM) + (FROG_DIM_Y * 2) + DENS_HEIGTH)
#define GAME_WIDTH 150
#define GAME_START (SCORE_HEIGHT)

#define GRASS_HEIGHT 4
#define GRASS_Y_SUP_START (DENS_Y_END)
#define GRASS_Y_SUP_END (GRASS_Y_SUP_START+GRASS_HEIGHT)

#define RIVER_HEIGHT (FROG_DIM_Y * N_STREAM)
#define RIVER_Y_START (GRASS_Y_SUP_END)
#define RIVER_Y_END (RIVER_Y_START+RIVER_HEIGHT)

#define GRASS_Y_INF_START (RIVER_Y_END)
#define GRASS_Y_INF_END (GRASS_Y_INF_START+GRASS_HEIGHT)

// Functions Prototypes
void init_screen();
void init_colors();
int rand_range(int min0, int max0);
void debuglog(char *message, int arg);