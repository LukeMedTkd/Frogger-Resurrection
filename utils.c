#include <time.h>
#include "utils.h"

void init_screen(){
    // Setup screen
    setlocale(LC_ALL, ""); // Enable UTF-8 chars
    initscr(); // Initialize window
    noecho(); // Hide character typed
    curs_set(0); // Remove cursor
    cbreak(); // Don't wait ENTER in getch()
    keypad(stdscr, TRUE); // Enable function keys listener
    nodelay(stdscr, TRUE);
    srand(time(0));
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
    init_color(COLOR_FROG, 70, 350, 70);
    init_color(COLOR_LEGS, 58, 392, 19);
    init_color(COLOR_RIVER, 215, 570, 800);
    init_color(COLOR_CROCODILE_BODY, 78, 352, 117);
    init_color(COLOR_CROCODILE_SCALES, 39, 196, 39);
    init_color(COLOR_DENS, 568, 250, 205);
    init_color(COLOR_GRASS, 245, 570, 200);
    init_color(COLOR_SCORE, 25, 25, 25);
    

    // Background Color
    init_pair(COLOR_RIVER_ID, COLOR_RIVER, COLOR_RIVER);
    init_pair(COLOR_GRASS_ID, COLOR_GRASS, COLOR_GRASS);    
    init_pair(COLOR_DENS_ID, COLOR_DENS, COLOR_DENS);
    init_pair(COLOR_SCORE_ID, COLOR_WHITE, COLOR_SCORE); 

    // Entities Colors 
    init_pair(COLOR_FROG_ID, COLOR_FROG, COLOR_LEGS);
    init_pair(COLOR_EYE_ID, COLOR_BLACK, COLOR_FROG);
    init_pair(COLOR_LEGS_ID, COLOR_LEGS, COLOR_FROG);
    init_pair(COLOR_CROCODILE_BODY_ID, COLOR_CROCODILE_BODY, COLOR_RIVER);
    init_pair(COLOR_CROCODILE_SCALES_ID, COLOR_CROCODILE_SCALES, COLOR_CROCODILE_BODY);

}

int rand_range(int max0, int min0){
    return rand() % (max0 - min0 + 1) + min0;
}

void debuglog(char *message, int arg){
    FILE *f = fopen(DEBUG_FILE_NAME, "a");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, message, arg);
    fclose(f);
}