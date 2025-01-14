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
    use_default_colors();

    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_WHITE, 255, 255, 255);
    init_color(COLOR_RED, 255, 0, 0);
    init_color(COLOR_GREEN, 0, 128, 0);
    init_color(COLOR_YELLOW, 255, 255, 0);
    init_color(COLOR_BLUE, 0, 0, 255);
    init_color(COLOR_MAGENTA, 255, 0, 255);
    init_color(COLOR_CYAN, 0, 255, 255);
    init_color(COLOR_FROG, 55, 166, 43);
    init_color(COLOR_RIVER, 215, 570, 800);
    init_color(COLOR_CROCODILLE, 29, 87, 23);
    init_color(COLOR_DENS, 568, 250, 205);
    init_color(COLOR_GRASS, 245, 570, 200);
    init_color(COLOR_SCORE, 25, 25, 25);
    

    // (text, bg)
    init_pair(COLOR_FROG_ID, COLOR_WHITE, COLOR_FROG);
    init_pair(COLOR_RIVER_ID, COLOR_WHITE, COLOR_RIVER);
    init_pair(COLOR_CROCODILLE_ID, COLOR_WHITE, COLOR_CROCODILLE);
    init_pair(COLOR_DENS_ID, COLOR_WHITE, COLOR_DENS);
    init_pair(COLOR_SCORE_ID, COLOR_WHITE, COLOR_SCORE); 
    init_pair(COLOR_GRASS_ID, COLOR_WHITE, COLOR_GRASS);     

}


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
    mvprintw(LINES, 4, "cioa");
    refresh();
    sleep(20);
    endwin();
}