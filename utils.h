// Include Lib
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <locale.h>

// Defined Color_Id
#define COLOR_FROG 10
#define COLOR_RIVER 11
#define COLOR_CROCODILLE 12
#define COLOR_DENS 13
#define COLOR_GRASS 14
#define COLOR_SCORE 15

// Defined Color_Pair_Id
#define COLOR_FROG_ID 20
#define COLOR_RIVER_ID 21
#define COLOR_CROCODILLE_ID 22
#define COLOR_DENS_ID 23
#define COLOR_GRASS_ID 24
#define COLOR_SCORE_ID 25


// Defined sizes of game area
#define SCORE_HEIGHT (3)
#define GAME_HEIGHT (LINES-SCORE_HEIGHT)

#define DENS_HEIGTH (LINES/9)
#define DENS_Y_START (SCORE_HEIGHT)
#define DENS_Y_END (SCORE_HEIGHT+DENS_HEIGTH)

#define GRASS_HEIGHT (LINES/9)
#define GRASS_Y_SUP_START (SCORE_HEIGHT+DENS_HEIGTH)
#define GRASS_Y_SUP_END (SCORE_HEIGHT+DENS_HEIGTH+GRASS_HEIGHT)

#define RIVER_HEIGHT (LINES/2)
#define RIVER_Y_START (SCORE_HEIGHT+DENS_HEIGTH+GRASS_HEIGHT)
#define RIVER_Y_END (SCORE_HEIGHT+DENS_HEIGTH+GRASS_HEIGHT+RIVER_HEIGHT)

#define GRASS_Y_INF_START (SCORE_HEIGHT+DENS_HEIGTH+GRASS_HEIGHT+RIVER_HEIGHT)
#define GRASS_Y_INF_END (SCORE_HEIGHT+DENS_HEIGTH+GRASS_HEIGHT+RIVER_HEIGHT+GRASS_HEIGHT)

// Function's prototypes
void init_screen();
void init_colors();
void print_game_area();