#include "sprites.h"
#include "utils.h"
#include "entity.h"

void print_timer(WINDOW *score, int timer){
    for(int j = 0; j < TIME; j++) mvwprintw(score, 0, GAME_WIDTH - TIME + j, " ");

    for (int i = (GAME_WIDTH - 1); i > (GAME_WIDTH - timer); i--){
        mvwprintw(score, 0, GAME_WIDTH - TIME - 8, "TIME: ");
        if(timer < 60 && timer > 56) wattron(score, COLOR_PAIR(COLOR_TIME1_ID) | A_BOLD);
        if(timer <= 56 && timer > 52) wattron(score, COLOR_PAIR(COLOR_TIME2_ID) | A_BOLD);
        if(timer <= 52 && timer > 48) wattron(score, COLOR_PAIR(COLOR_TIME3_ID) | A_BOLD);
        if(timer <= 48 && timer > 44) wattron(score, COLOR_PAIR(COLOR_TIME4_ID) | A_BOLD);
        if(timer <= 44 && timer > 40) wattron(score, COLOR_PAIR(COLOR_TIME5_ID) | A_BOLD);
        if(timer <= 40 && timer > 36) wattron(score, COLOR_PAIR(COLOR_TIME6_ID) | A_BOLD);
        if(timer <= 36 && timer > 32) wattron(score, COLOR_PAIR(COLOR_TIME7_ID) | A_BOLD);
        if(timer <= 32 && timer > 28) wattron(score, COLOR_PAIR(COLOR_TIME8_ID) | A_BOLD);
        if(timer <= 28 && timer > 24) wattron(score, COLOR_PAIR(COLOR_TIME9_ID) | A_BOLD);
        if(timer <= 24 && timer > 20) wattron(score, COLOR_PAIR(COLOR_TIME10_ID) | A_BOLD);
        if(timer <= 20 && timer > 16) wattron(score, COLOR_PAIR(COLOR_TIME11_ID) | A_BOLD);
        if(timer <= 16 && timer > 12) wattron(score, COLOR_PAIR(COLOR_TIME12_ID) | A_BOLD);
        if(timer <= 12 && timer > 8) wattron(score, COLOR_PAIR(COLOR_TIME13_ID) | A_BOLD);
        if(timer <= 8 && timer > 4) wattron(score, COLOR_PAIR(COLOR_TIME14_ID) | A_BOLD | A_BLINK);
        if(timer <= 4 && timer > 0) wattron(score, COLOR_PAIR(COLOR_TIME15_ID) | A_BOLD | A_BLINK);
        mvwprintw(score, 0, i, "█");
    }
    wattroff(score, COLOR_PAIR(COLOR_TIME1_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME2_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME3_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME4_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME5_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME6_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME7_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME8_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME9_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME10_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME11_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME12_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME13_ID) | A_BOLD);
    wattroff(score, COLOR_PAIR(COLOR_TIME14_ID) | A_BOLD | A_BLINK);
    wattroff(score, COLOR_PAIR(COLOR_TIME15_ID) | A_BOLD | A_BLINK);
    
}

void print_score(WINDOW *score, int vscore){
    wattron(score, COLOR_PAIR(COLOR_SCORE_ID) | A_BOLD);
    mvwprintw(score, 0, GAME_WIDTH/3, "SCORE: %d", vscore);
    wattroff(score, COLOR_PAIR(COLOR_SCORE_ID) | A_BOLD);
}

void print_lifes(WINDOW *score, int lifes){
    wattron(score, COLOR_PAIR(COLOR_LIFES_ID) | A_BOLD);
    mvwprintw(score, 0, 1, "LIFES: ");
    mvwprintw(score, 0, 7, "%s", "                         ");
    for (int i = 0; i < lifes; i++){
        if(lifes < 3) wattron(score, A_BLINK);
        mvwprintw(score, 0, (8 + (i*3)), "%s", "🐸");
    }
    wattroff(score, A_BLINK);
    wattroff(score, COLOR_PAIR(COLOR_LIFES_ID) | A_BOLD);
}

void print_game_area(WINDOW *game, bool *dens){
    // Dens
    for (int y = DENS_Y_START; y < DENS_Y_END; y++){
        for (int x = 0; x < GAME_WIDTH; x++){
            if ((dens[0] == TRUE) && (x >= DENS1_START && x < (DENS1_START + FROG_DIM_X)) && (y > DENS_Y_START)){
                wattron(game, COLOR_PAIR(COLOR_GRASS_ID));
                mvwprintw(game, y, x, "%c", ' ');
                wattroff(game, COLOR_PAIR(COLOR_GRASS_ID));
                continue;
            }

            if ((dens[1] == TRUE) && (x >= DENS2_START && x < (DENS2_START + FROG_DIM_X) && (y > DENS_Y_START))){
                wattron(game, COLOR_PAIR(COLOR_GRASS_ID));
                mvwprintw(game, y, x, "%c", ' ');
                wattroff(game, COLOR_PAIR(COLOR_GRASS_ID));
                continue;
            }

            if ((dens[2] == TRUE) && (x >= DENS3_START && x < (DENS3_START + FROG_DIM_X) && (y > DENS_Y_START))){
                wattron(game,COLOR_PAIR(COLOR_GRASS_ID));
                mvwprintw(game, y, x, "%c", ' ');
                wattroff(game,COLOR_PAIR(COLOR_GRASS_ID));
                continue;
            }

            if ((dens[3] == TRUE) && (x >= DENS4_START && x < (DENS4_START + FROG_DIM_X) && (y > DENS_Y_START))){
                wattron(game,COLOR_PAIR(COLOR_GRASS_ID));
                mvwprintw(game, y, x, "%c", ' ');
                wattroff(game,COLOR_PAIR(COLOR_GRASS));
                continue;
            }

            if ((dens[4] == TRUE) && (x >= DENS5_START && x < (DENS5_START + FROG_DIM_X) && (y > DENS_Y_START))){
                wattron(game,COLOR_PAIR(COLOR_GRASS_ID));
                mvwprintw(game, y, x, "%c", ' ');
                wattroff(game,COLOR_PAIR(COLOR_GRASS_ID));
                continue;
            }

            wattron(game, COLOR_PAIR(COLOR_DENS_ID));
            mvwprintw(game, y, x, "%c", ' ');
            wattroff(game, COLOR_PAIR(COLOR_DENS_ID));
        }
    }

    
    // Upper edge
    wattron(game, COLOR_PAIR(COLOR_GRASS_ID));
    for (int y = GRASS_Y_SUP_START; y < GRASS_Y_SUP_END; y++){
        mvwhline(game, y, 0, ' ', GAME_WIDTH);
    }
    wattroff(game, COLOR_PAIR(COLOR_GRASS_ID));

    // River
    wattron(game, COLOR_PAIR(COLOR_RIVER_ID));
    for (int y = RIVER_Y_START; y < RIVER_Y_END; y++){
        mvwhline(game, y, 0, ' ', GAME_WIDTH);
    }
    wattroff(game, COLOR_PAIR(COLOR_RIVER_ID));

    // Bottom edge
    wattron(game, COLOR_PAIR(COLOR_GRASS_ID));
    for (int y = GRASS_Y_INF_START; y < GRASS_Y_INF_END; y++){
        mvwhline(game, y, 0, ' ', GAME_WIDTH);
    }
    wattroff(game, COLOR_PAIR(COLOR_GRASS_ID));
}

void print_frog(WINDOW *game, Character frog_entity) {
    // Defined Frog Sprite
    static const char* frog[FROG_DIM_Y][FROG_DIM_X] = {
       {"▄", "█", "", "▀", "▌", "▐", "▀", "", "█", "▄"},
        {"", "▀", "▄", " ", "▄", " ", " ", "▄", "▀", ""},
        {"", "", "▄", "█", "▄", "▀", "▄", "▄", "", ""},
        {"▀", "█", "▀", "", "", "", "", "▀", "█", "▀"},

    };



    for (int i = 0; i < FROG_DIM_Y; i++) {
        for (int j = 0; j < FROG_DIM_X; j++) {
            if (frog[i][j][0] == '\0') {
                continue; // Salta le posizioni vuote
            }

            // Determina il colore
            if (i == 0) {
                wattron(game, COLOR_PAIR(COLOR_EYE_ID));
            } else if (i == 2 && (j == 0 || j == 1 || j == 4 || j == 5)) {
                wattron(game, COLOR_PAIR(COLOR_LEGS_ID));
            } else {
                wattron(game, COLOR_PAIR(COLOR_FROG_ID));
            }

            // Stampa il carattere
            mvwprintw(game, frog_entity.y + i, frog_entity.x + j, "%s", frog[i][j]);

            // Ripristina il colore
            if (i == 0 || (i == 2 && (j == 0 || j == 1 || j == 4 || j == 5))) {
                wattroff(game, COLOR_PAIR(COLOR_EYE_ID));
                wattroff(game, COLOR_PAIR(COLOR_LEGS_ID));
            } else {
                wattroff(game, COLOR_PAIR(COLOR_FROG_ID));
            }
        }
    }
}

void print_crocodiles(WINDOW *game, Character *Entities, int *stream_speed_with_dir){

    // Define 2 crocodile sprites
    static const char* items[2][4][30] = {
        {//SX-DX
            {"", "", "", "", "▀", "▀", "▀", "█", "█", "█", "▄", "▄", "▄", "▄", "▄", "▄", "▄", "▄", "▄", "▄", "▄", "▄", "█", "█", "▀", "▀", "▀", "", "", ""},
            {"▄", "▄", "▄", "▄", " ", "▄", " ", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", " ", "▀", "█", "▄", "▄", "▄"},
            {"▀", "▀", "▀", "▀", " ", "▀", " ", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", " ", "▄", "█", "▀", "▀", "▀"},
            {"", "", "", "", "▄", "▄", "▄", "█", "█", "█", "▀", "▀", "▀", "▀", "▀", "▀", "▀", "▀", "▀", "▀", "▀", "▀", "█", "█", "▄", "▄", "▄", "", "", ""}
        },
        {//DX-SX
            {"", "", "", "", "▀", "▀", "▀", "█", "█", "█", "▄", "▄", "▄", "▄", "▄", "▄", "▄", "▄", "▄", "▄", "▄", "▄", "█", "█", "▀", "▀", "▀", "", "", ""},
            {"▄", "▄", "▄", "█", "▀", " ", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", " ", "▄"," ","▄", "▄", "▄", "▄"},
            {"▀", "▀", "▀", "█", "▄", " ", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", "▄", "▀", " ", "▀"," ","▀", "▀", "▀", "▀"},
            {"", "", "", "", "▄", "▄", "▄", "█", "█", "█", "▀", "▀", "▀", "▀", "▀", "▀", "▀", "▀", "▀", "▀", "▀", "▀", "█", "█", "▄", "▄", "▄", "", "", ""}
        }
    };

    // Variables Statement
    int dir, n_stream, sprite_index;

    for(int n = FIRST_CROCODILLE; n < LAST_CROCODILLE; n++){
        // Set n_stream index from 0 to 7
        n_stream = (n - FIRST_CROCODILLE) / MAX_N_CROCODILE_PER_STREAM;
        if(n_stream > 7) n_stream = 7;

        // Get direction
        dir = (stream_speed_with_dir[n_stream] > 0 ? 1 : -1);
    
        // Get sprite_index
        sprite_index = (dir == 1 ? 0 : 1);

        // Print
        for(int i = 0; i < CROCODILE_DIM_Y; i++){
            for(int j = 0; j < CROCODILE_DIM_X; j++){
                if (sprite_index == 0 && (i == 1 || i ==2) && (j == 25)){
                    wattron(game, COLOR_PAIR(COLOR_CROCODILE_EYES_ID));
                    mvwprintw(game, Entities[n].y + i, Entities[n].x + j, "%s", items[sprite_index][i][j]);
                    wattroff(game, COLOR_PAIR(COLOR_CROCODILE_EYES_ID));
                }
                else if (sprite_index == 1 && (i == 1 || i ==2) && (j == 4)){
                    wattron(game, COLOR_PAIR(COLOR_CROCODILE_EYES_ID));
                    mvwprintw(game, Entities[n].y + i, Entities[n].x + j, "%s", items[sprite_index][i][j]);
                    wattroff(game, COLOR_PAIR(COLOR_CROCODILE_EYES_ID));
                }
                
                else if((i == 1 || i == 2) && (j > 5 && j < 24)){
                    wattron(game,COLOR_PAIR(COLOR_CROCODILE_SCALES_ID));
                    mvwprintw(game, Entities[n].y + i, Entities[n].x + j, "%s", items[sprite_index][i][j]); 
                    wattroff(game, COLOR_PAIR(COLOR_CROCODILE_SCALES_ID));
                }
                else{
                    wattron(game, COLOR_PAIR(COLOR_CROCODILE_BODY_ID));
                    mvwprintw(game, Entities[n].y + i, Entities[n].x + j, "%s", items[sprite_index][i][j]); 
                    wattroff(game, COLOR_PAIR(COLOR_CROCODILE_BODY_ID));
                }
            }
        }
    }
}