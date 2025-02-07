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
#define COLOR_LEGS 110
#define COLOR_RIVER 120
#define COLOR_CROCODILE_BODY 130
#define COLOR_CROCODILE_SCALES 140
#define COLOR_CROCODILE_EYES 141
#define COLOR_DENS 150
#define COLOR_GRASS 151
#define COLOR_SCORE 152
#define COLOR_LIFES 153
#define COLOR_TIME1 154
#define COLOR_TIME2 155
#define COLOR_TIME3 156
#define COLOR_TIME4 157
#define COLOR_TIME5 158
#define COLOR_TIME6 156
#define COLOR_TIME7 160
#define COLOR_TIME8 161
#define COLOR_TIME9 162
#define COLOR_TIME10 163
#define COLOR_TIME11 164
#define COLOR_TIME12 165
#define COLOR_TIME13 166
#define COLOR_TIME14 167
#define COLOR_TIME15 168
#define COLOR_BKG_LOST_GAME 169
#define COLOR_WRT_LOST_GAME 170
#define COLOR_BKG_TIME_IS_UP 171
#define COLOR_WRT_TIME_IS_UP 172
#define COLOR_BKG_WON_GAME 173
#define COLOR_WRT_WON_GAME 174


// Defined Color_Pair_Id
#define COLOR_FROG_ID 200
#define COLOR_EYE_ID 201
#define COLOR_LEGS_ID 202
#define COLOR_RIVER_ID 203
#define COLOR_CROCODILE_BODY_ID 204
#define COLOR_CROCODILE_SCALES_ID 205
#define COLOR_DENS_ID 206
#define COLOR_GRASS_ID 207
#define COLOR_SCORE_ID 208
#define COLOR_LIFES_ID 209
#define COLOR_TIME1_ID 210
#define COLOR_TIME2_ID 211
#define COLOR_TIME3_ID 212
#define COLOR_TIME4_ID 213
#define COLOR_TIME5_ID 214
#define COLOR_TIME6_ID 215
#define COLOR_TIME7_ID 216
#define COLOR_TIME8_ID 217
#define COLOR_TIME9_ID 218
#define COLOR_TIME10_ID 219
#define COLOR_TIME11_ID 220
#define COLOR_TIME12_ID 221
#define COLOR_TIME13_ID 222
#define COLOR_TIME14_ID 223
#define COLOR_TIME15_ID 224
#define COLOR_CROCODILE_EYES_ID 225
#define COLOR_BKG_LOST_GAME_ID 226
#define COLOR_WRT_LOST_GAME_ID 227
#define COLOR_BKG_TIME_IS_UP_ID 228
#define COLOR_WRT_TIME_IS_UP_ID 229
#define COLOR_BKG_WON_GAME_ID 230
#define COLOR_WRT_WON_GAME_ID 231


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
void center_game(WINDOW *score, WINDOW *game);
int rand_range(int max, int min);
void debuglog(char *message, int arg);