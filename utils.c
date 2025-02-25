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
    srand(time(NULL));
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
    init_color(COLOR_FROG, 156, 509, 0);
    init_color(COLOR_LEGS, 120, 470, 55);
    init_color(COLOR_RIVER, 215, 570, 800);
    init_color(COLOR_CROCODILE_BODY, 78, 352, 117);
    init_color(COLOR_CROCODILE_SCALES, 39, 196, 39);
    init_color(COLOR_CROCODILE_EYES, 66, 78, 66);
    init_color(COLOR_CROCODILE_BULLETS, 274, 235, 392);
    init_color(COLOR_DENS, 568, 250, 205);
    init_color(COLOR_GRASS, 167, 570, 200);
    init_color(COLOR_SCORE, 745, 78, 78);
    init_color(COLOR_LIFES, 717, 815, 98);
    init_color(COLOR_TIME1, 717, 765, 98);
    init_color(COLOR_TIME2, 815, 715, 98);
    init_color(COLOR_TIME3, 815, 665, 98);
    init_color(COLOR_TIME4, 815, 615, 98);
    init_color(COLOR_TIME5, 815, 565, 98);
    init_color(COLOR_TIME6, 815, 515, 98);
    init_color(COLOR_TIME7, 815, 465, 98);
    init_color(COLOR_TIME8, 815, 415, 98);
    init_color(COLOR_TIME9, 815, 365, 98);
    init_color(COLOR_TIME10, 815, 315, 98);
    init_color(COLOR_TIME11, 815, 265, 98);
    init_color(COLOR_TIME12, 815, 215, 98);
    init_color(COLOR_TIME13, 815, 165, 98);
    init_color(COLOR_TIME14, 815, 115, 98);
    init_color(COLOR_TIME15, 815, 65, 98);
    init_color(COLOR_BKG_WON_GAME, 925, 741, 458);
    init_color(COLOR_WRT_WON_GAME, 541, 329, 309);
    init_color(COLOR_BKG_TIME_IS_UP, 247, 254, 286);
    init_color(COLOR_WRT_TIME_IS_UP, 839, 149, 211);
    init_color(COLOR_BKG_LOST_GAME, 192, 62, 101);
    init_color(COLOR_WRT_LOST_GAME, 611, 192, 129);
    init_color(COLOR_BKG_DEMO, 607, 690, 223);
    init_color(COLOR_WRT_DEMO, 945, 282, 207);
    init_color(COLOR_BKG_WRT_DEMO, 454, 231, 160);
    init_color(COLOR_BKG_TERM, 125, 67, 67);
    init_color(COLOR_WRT_TERM, 921, 882, 882);


    // Time Colors
    init_pair(COLOR_TIME1_ID, COLOR_TIME1, COLOR_BLACK);
    init_pair(COLOR_TIME2_ID, COLOR_TIME2, COLOR_BLACK);
    init_pair(COLOR_TIME3_ID, COLOR_TIME3, COLOR_BLACK);
    init_pair(COLOR_TIME4_ID, COLOR_TIME4, COLOR_BLACK);
    init_pair(COLOR_TIME5_ID, COLOR_TIME5, COLOR_BLACK);
    init_pair(COLOR_TIME6_ID, COLOR_TIME6, COLOR_BLACK);
    init_pair(COLOR_TIME7_ID, COLOR_TIME7, COLOR_BLACK);
    init_pair(COLOR_TIME8_ID, COLOR_TIME8, COLOR_BLACK);
    init_pair(COLOR_TIME9_ID, COLOR_TIME9, COLOR_BLACK);
    init_pair(COLOR_TIME10_ID, COLOR_TIME10, COLOR_BLACK);
    init_pair(COLOR_TIME11_ID, COLOR_TIME11, COLOR_BLACK);
    init_pair(COLOR_TIME12_ID, COLOR_TIME12, COLOR_BLACK);
    init_pair(COLOR_TIME13_ID, COLOR_TIME13, COLOR_BLACK);
    init_pair(COLOR_TIME14_ID, COLOR_TIME14, COLOR_BLACK);
    init_pair(COLOR_TIME15_ID, COLOR_TIME15, COLOR_BLACK);
    init_pair(COLOR_TERM_ID, COLOR_WRT_TERM, COLOR_BKG_TERM);
    

    // Background Colors
    init_pair(COLOR_RIVER_ID, COLOR_RIVER, COLOR_RIVER);
    init_pair(COLOR_GRASS_ID, COLOR_GRASS, COLOR_GRASS);    
    init_pair(COLOR_DENS_ID, COLOR_DENS, COLOR_DENS);
    init_pair(COLOR_SCORE_ID, COLOR_SCORE, COLOR_BLACK); 
    init_pair(COLOR_LIFES_ID, COLOR_LIFES, COLOR_BLACK);
    init_pair(COLOR_BKG_LOST_GAME_ID, COLOR_BKG_LOST_GAME, COLOR_BKG_LOST_GAME);
    init_pair(COLOR_WRT_LOST_GAME_ID, COLOR_WRT_LOST_GAME, COLOR_BKG_LOST_GAME);
    init_pair(COLOR_BKG_TIME_IS_UP_ID, COLOR_BKG_TIME_IS_UP, COLOR_BKG_TIME_IS_UP);
    init_pair(COLOR_WRT_TIME_IS_UP_ID, COLOR_WRT_TIME_IS_UP, COLOR_BKG_TIME_IS_UP);
    init_pair(COLOR_BKG_WON_GAME_ID, COLOR_BKG_WON_GAME, COLOR_BKG_WON_GAME);
    init_pair(COLOR_WRT_WON_GAME_ID, COLOR_WRT_WON_GAME, COLOR_BKG_WON_GAME);
    init_pair(COLOR_BKG_DEMO_ID, COLOR_BKG_DEMO, COLOR_BKG_DEMO);
    init_pair(COLOR_WRT_DEMO_ID, COLOR_WRT_DEMO, COLOR_BKG_DEMO);

    // Entities Colors 
    init_pair(COLOR_FROG_ID, COLOR_FROG, COLOR_LEGS);
    init_pair(COLOR_EYE_ID, COLOR_BLACK, COLOR_FROG);
    init_pair(COLOR_LEGS_ID, COLOR_LEGS, COLOR_FROG);
    init_pair(COLOR_CROCODILE_BODY_ID, COLOR_CROCODILE_BODY, COLOR_RIVER);
    init_pair(COLOR_CROCODILE_SCALES_ID, COLOR_CROCODILE_SCALES, COLOR_CROCODILE_BODY);
    init_pair(COLOR_CROCODILE_EYES_ID, COLOR_CROCODILE_EYES, COLOR_CROCODILE_BODY);
    init_pair(COLOR_CROCODILE_BULLETS_ID, COLOR_CROCODILE_BULLETS, COLOR_CROCODILE_BULLETS);

}

void center_game(WINDOW *score, WINDOW *game){
    int start_y = (LINES - GAME_HEIGHT) / 2;
    int start_x = (COLS - GAME_WIDTH) / 2;
    mvwin(score, start_y, start_x);
    mvwin(game, start_y + 1, start_x);
}

void check_terminal_size(){
    if(LINES < GAME_HEIGHT || COLS < GAME_WIDTH){
        WINDOW *resize_term = newwin(0,0,0,0);
        wbkgd(resize_term, COLOR_PAIR(COLOR_TERM_ID));
        while( LINES < GAME_HEIGHT || COLS < GAME_WIDTH){
            wattron(resize_term ,A_BOLD);
            mvwprintw(resize_term, 1, 3, "RULES FOR A GOOD GAMING EXPERIENCE");
            wattroff(resize_term ,A_BOLD);
            mvwprintw(resize_term, 3, 3, "Make sure that full screen is enabled");
            mvwprintw(resize_term, 6, 5, "The window is too small for playing");
            mvwprintw(resize_term, 7, 5, "Minimum size allowed; %d x %d", GAME_WIDTH, GAME_HEIGHT);
            mvwprintw(resize_term, 8, 5, "Current Size; %d x %d", COLS, LINES);
            mvwprintw(resize_term, 9, 5, "If the full screen is too small, click on 'Ctrl -'");
            wrefresh(resize_term);
        }
        delwin(resize_term);
        clear();
        refresh();
    }
    return;
}

int rand_range(int max, int min){
    return rand() % (max - min + 1) + min;
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

void logExecutionTime(){
    static struct timespec start, end;
    static int first_call = 1;

    if(first_call){
        // First Call - Store start time
        clock_gettime(CLOCK_MONOTONIC, &start);
        first_call = 0;
    } 
    
    else{
        // Second Call - Computes execution time and writes it on the file 
        clock_gettime(CLOCK_MONOTONIC, &end);

        // Compute the time spent
        long seconds = end.tv_sec - start.tv_sec;
        long nanoseconds = end.tv_nsec - start.tv_nsec;
        double elapsed = seconds + nanoseconds * 1e-9;

        // Writes the outcome on the file
        FILE *fp = fopen(LOG_TIME_FILE_NAME, "a");
        if (fp == NULL) {
            perror("fopen");
            return;
        }
        fprintf(fp, "Tempo di esecuzione: %.9f secondi\n", elapsed);
        fclose(fp);

        // Resets for the next test
        first_call = 1;
    }
}
