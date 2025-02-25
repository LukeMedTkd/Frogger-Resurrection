#include <string.h>
#include "utils.h"
#include "game.h"
#include "sprites.h"
#include "sound.h"

#define MENU_HEIGHT 46
#define MENU_WIDTH 150
#define MENU_OPTIONS 2
#define SPACE_BETWEEN_OPTIONS 2
#define SPACE_BETWEEN_TITLE 3

extern Sound sounds[N_SOUND];

int start_menu(WINDOW *menu) {

    // The keypad option enables the keypad of the user's terminal (from the official terminal)
    keypad(menu, TRUE);
    int key, choice = 0;
    const char *options[MENU_OPTIONS] = {" START ", " QUIT "};

    while (1){

        // Print the background
        wbkgd(menu, COLOR_PAIR(COLOR_WRT_DEMO_ID));

        draw_von_neumann_machine(menu);

        // Print the TITLE
        wattron(menu, COLOR_PAIR(COLOR_WRT_DEMO_ID) | A_BOLD);
        mvwprintw(menu, (MENU_HEIGHT/2) - ((MENU_OPTIONS + SPACE_BETWEEN_OPTIONS + SPACE_BETWEEN_TITLE + 1)/2), ((GAME_WIDTH/2) - (20 / 2)), "%s", "FROGGER RESURRECTION");
        mvwprintw(menu, (MENU_HEIGHT/2) - ((MENU_OPTIONS + SPACE_BETWEEN_OPTIONS + SPACE_BETWEEN_TITLE)/2), ((GAME_WIDTH/2) - (30 / 2)), "%s", "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾");
        wattroff(menu, COLOR_PAIR(COLOR_WRT_DEMO_ID) | A_BOLD);

        // Print the 2 OPTIONS (START or QUIT)
        for (int i = 0; i < MENU_OPTIONS; i++){
            if (i == choice){
                wattron(menu, COLOR_PAIR(COLOR_WRT_DEMO_ID) | A_REVERSE | A_BOLD);
            }
            mvwprintw(menu, (MENU_HEIGHT/2) - ((MENU_OPTIONS + SPACE_BETWEEN_OPTIONS + SPACE_BETWEEN_TITLE)/2 - SPACE_BETWEEN_TITLE) + i*SPACE_BETWEEN_OPTIONS, ((MENU_WIDTH/2) - (strlen(options[i]) / 2)), "%s", options[i]);
            wattroff(menu, COLOR_PAIR(COLOR_WRT_DEMO_ID) | A_REVERSE | A_BOLD);
        }

        // User Input
        key = wgetch(menu);
        switch (key) {
            case KEY_UP:
                choice = (choice - 1 + MENU_OPTIONS) % MENU_OPTIONS;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % MENU_OPTIONS;
                break;
            case 10:
                return choice == 0 ? 1 : 0; // 1 = START, 0 = QUIT
        }

        wrefresh(menu); 
    }
}

int main(){

    // Init the screen
    init_screen();

    // Set the game colors
    init_colors();

    // Check the terminal size
    check_terminal_size();

    // Create the MENU window
    WINDOW *menu = newwin(MENU_HEIGHT, MENU_WIDTH, ((LINES/2)-(MENU_HEIGHT/2)), ((COLS/2)-(MENU_WIDTH/2)));

    // Initialize miniaudio engine
    init_ma_engine(sounds);
    
    // Menu LOOP
    while (1) {
        
        // Play DEMO Sound
        play_sound(&sounds[DEMO].sound);
        
        // Print demo
        print_demo(menu);

        // Stop DEMO Sound
        stop_sound(&sounds[DEMO].sound);

        if(!start_menu(menu)) break; // If the USER click QUIT, break

        // Clear the INITSCR then remove the menu window
        clear();
        refresh();

        // Create the two GAME windows
        WINDOW *score = newwin(SCORE_HEIGHT, GAME_WIDTH, 0, 0);
        WINDOW *game = newwin(GAME_HEIGHT, GAME_WIDTH, GAME_START, 0);

        // Center the entire screen
        center_game(score, game);

        // Start the entire game
        start_game(score, game);
    }

    delwin(menu);
    endwin();
    return 0;
}