#include "sprites.h"
#include "utils.h"
#include "entity.h"

void print_game_area(WINDOW *game){
    // Dens
    wattron(game, COLOR_PAIR(COLOR_DENS_ID));
    for (int y = DENS_Y_START; y < DENS_Y_END; y++){
        mvwhline(game, y, 0, ' ', COLS);
    }
    wattroff(game, COLOR_PAIR(COLOR_DENS_ID));
    
    // Upper edge
    wattron(game, COLOR_PAIR(COLOR_GRASS_ID));
    for (int y = GRASS_Y_SUP_START; y < GRASS_Y_SUP_END; y++){
        mvwhline(game, y, 0, ' ', COLS);
    }
    wattroff(game, COLOR_PAIR(COLOR_GRASS_ID));

    // River
    wattron(game, COLOR_PAIR(COLOR_RIVER_ID));
    for (int y = RIVER_Y_START; y < RIVER_Y_END; y++){
        mvwhline(game, y, 0, ' ', COLS);
    }
    wattroff(game, COLOR_PAIR(COLOR_RIVER_ID));

    // Bottom edge
    wattron(game, COLOR_PAIR(COLOR_GRASS_ID));
    for (int y = GRASS_Y_INF_START; y < GRASS_Y_INF_END; y++){
        mvwhline(game, y, 0, ' ', COLS);
    }
    wattroff(game, COLOR_PAIR(COLOR_GRASS_ID));
}

void print_frog(WINDOW *game, Character frog_entity) {
    // Defined Frog Sprite
    static const char* frog[FROG_DIM_Y][FROG_DIM_X] = {
       {"", "", "▖", "▗", "", ""},
       {"", "", "▟", "▀", "▙", ""},
       {"▝", "▟", "▀", "▀", "▙", "▘"},

    };



    for (int i = 0; i < FROG_DIM_Y; i++) {
        for (int j = 0; j < FROG_DIM_X; j++) {
            if (frog[i][j][0] == '\0') {
                continue; // Salta le posizioni vuote
            }

            // Determina il colore
            if (i == 0) {
                wattron(game, COLOR_PAIR(COLOR_EYE_ID));
            } else if (i == 2 && (j == 0 || j == 1 || j == 4 || j == 5)) {
                wattron(game, COLOR_PAIR(COLOR_LEGS_ID));
            } else {
                wattron(game, COLOR_PAIR(COLOR_FROG_ID));
            }

            // Stampa il carattere
            mvwprintw(game, frog_entity.y + i, frog_entity.x + j, "%s", frog[i][j]);

            // Ripristina il colore
            if (i == 0 || (i == 2 && (j == 0 || j == 1 || j == 4 || j == 5))) {
                wattroff(game, COLOR_PAIR(COLOR_EYE_ID));
                wattroff(game, COLOR_PAIR(COLOR_LEGS_ID));
            } else {
                wattroff(game, COLOR_PAIR(COLOR_FROG_ID));
            }
        }
    }
}
