#include "utils.h"

void init_screen(){
    // Setup screen
    setlocale(LC_ALL, ""); // Enable UTF-8 chars
    initscr(); // Initialize window
    noecho(); // Hide character typed
    curs_set(0); // Remove cursor
    cbreak(); // Don't wait ENTER in getch()
    keypad(stdscr, TRUE); // Enable function keys listener
}

void init_colors(){

    // Enable colors
    start_color();

    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_WHITE, 255, 255, 255);
    init_color(COLOR_RED, 255, 0, 0);
    init_color(COLOR_GREEN, 0, 128, 0);
    init_color(COLOR_YELLOW, 255, 255, 0);
    init_color(COLOR_BLUE, 0, 0, 255);
    init_color(COLOR_MAGENTA, 255, 0, 255);
    init_color(COLOR_CYAN, 0, 255, 255);
    init_color(COLOR_FROG, 55, 166, 43);
    init_color(COLOR_RIVER, 50, 90, 160);
    init_color(COLOR_CROCODILLE, 29, 87, 23);
    init_color(COLOR_DENS, 110, 70, 10);
    init_color(COLOR_GRASS, 10, 110, 20);
    init_color(COLOR_SCORE, 25, 25, 25);
    

    // (text, bg)
    init_pair(COLOR_FROG_ID, COLOR_BLACK, COLOR_FROG);
    init_pair(COLOR_RIVER_ID, COLOR_BLACK, COLOR_RIVER);
    init_pair(COLOR_CROCODILLE_ID, COLOR_BLACK, COLOR_CROCODILLE);
    init_pair(COLOR_DENS_ID, COLOR_BLACK, COLOR_DENS);
    init_pair(COLOR_SCORE_ID, COLOR_BLACK, COLOR_SCORE); 
    init_pair(COLOR_GRASS_ID, COLOR_BLACK, COLOR_GRASS);     

}


void print_game_area(){
    // Dens
    attron(COLOR_PAIR(COLOR_DENS_ID));
    for (int y = SCORE_HEIGHT; y < DENS_HEIGTH+SCORE_HEIGHT; y++){
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
        for (int x = 0; x < COLS; x++) {mvwaddch(stdscr, y, x, ' ');}
    }
    attroff(COLOR_PAIR(COLOR_RIVER_ID));

    // Bottom edge
    attron(COLOR_PAIR(COLOR_GRASS_ID));
    for (int y = GRASS_Y_INF_START; y < GRASS_Y_INF_END; y++){
        for (int x = 0; x < COLS; x++) {mvwaddch(stdscr, y, x, ' ');}
    }
    attroff(COLOR_PAIR(COLOR_GRASS_ID));

    refresh();
    sleep(20);
    endwin();
}