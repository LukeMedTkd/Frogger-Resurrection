#include "utils.h"
#include "game.h"

int main(){

    // Inits screen
    init_screen();
    // Creates two game windows
    WINDOW *score = newwin(SCORE_HEIGHT, GAME_WIDTH, 0, 0);
    WINDOW *game = newwin(GAME_HEIGHT, GAME_WIDTH, GAME_START, 0);

    // Centers entire screen
    center_game(score, game);

    // Sets colors
    init_colors();

    start_game(score, game);

    return 0;
}