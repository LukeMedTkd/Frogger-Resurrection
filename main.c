#include "utils.h"
#include "game.h"

int main(){

    // Init screen
    init_screen();

    // Create two game windows
    WINDOW *score = newwin(SCORE_HEIGHT, GAME_WIDTH, 0, 0);
    WINDOW *game = newwin(GAME_HEIGHT, GAME_WIDTH, GAME_START, 0);

    //set colors
    init_colors();

    start_game(score, game);

    return 0;
}