#include "utils.h"
#include "sprites.h"

void print_game_area(){
    // Dens
    attron(COLOR_PAIR(COLOR_DENS_ID));
    for (int y = SCORE_HEIGHT; y < GRASS_Y_SUP_START; y++){
        for (int x = 0; x < COLS; x++) {mvwaddch(stdscr, y, x, ' ');}
    }
    attroff(COLOR_PAIR(COLOR_DENS_ID));
    
    // Upper edge
    attron(COLOR_PAIR(COLOR_GRASS_ID));
    for (int y = GRASS_Y_SUP_START; y < GRASS_Y_SUP_END; y++){
        for (int x = 0; x < COLS; x++) {mvwaddch(stdscr, y, x, ' ');}
    }
    attroff(COLOR_PAIR(COLOR_GRASS_ID));

    // River
    attron(COLOR_PAIR(COLOR_RIVER_ID));
    for (int y = RIVER_Y_START; y < RIVER_Y_END; y++){
        // for (int x = 0; x < COLS; x++) {mvwaddch(stdscr, y, x, ' ');}
        mvhline(y, 0, ' ', COLS);
    }
    attroff(COLOR_PAIR(COLOR_RIVER_ID));

    // Bottom edge
    attron(COLOR_PAIR(COLOR_GRASS_ID));
    for (int y = GRASS_Y_INF_START; y < GRASS_Y_INF_END; y++){
        for (int x = 0; x < COLS; x++) {mvwaddch(stdscr, y, x, ' ');}
    }
    attroff(COLOR_PAIR(COLOR_GRASS_ID));
    refresh();
    endwin();
}