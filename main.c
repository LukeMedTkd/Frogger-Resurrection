#include "utils.h"

int main(){

    //init screen
    init_screen();
    WINDOW *score = newwin(SCORE_HEIGHT, COLS, 0, 0);

    //set colors
    init_colors();

    return 0;
}