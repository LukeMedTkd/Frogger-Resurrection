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
    init_color(COLOR_RIVER, 15, 75, 155);
    init_color(COLOR_CROCODILLE, 29, 87, 23);
    init_color(COLOR_DENS, 60, 35, 5);
    init_color(COLOR_GRASS, 45, 95, 35);
    init_color(COLOR_SCORE, 25, 25, 25);
    

    // (text, bg)
    init_pair(COLOR_FROG_ID, COLOR_WHITE, COLOR_FROG);
    init_pair(COLOR_RIVER_ID, COLOR_WHITE, COLOR_RIVER);
    init_pair(COLOR_CROCODILLE_ID, COLOR_WHITE, COLOR_CROCODILLE);
    init_pair(COLOR_DENS_ID, COLOR_WHITE, COLOR_DENS);
    init_pair(COLOR_SCORE_ID, COLOR_WHITE, COLOR_SCORE); 
    init_pair(COLOR_GRASS_ID, COLOR_WHITE, COLOR_GRASS);     

}