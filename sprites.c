#include "utils.h"
#include "entity.h"
#include "sprites.h"

void print_game_area(WINDOW *game){
    // Dens
    attron(COLOR_PAIR(COLOR_DENS_ID));
    for (int y = SCORE_HEIGHT; y < GRASS_Y_SUP_START; y++){
        for (int x = 0; x < COLS; x++) {mvwaddch(game, y, x, ' ');}
    }
    attroff(COLOR_PAIR(COLOR_DENS_ID));
    
    // Upper edge
    attron(COLOR_PAIR(COLOR_GRASS_ID));
    for (int y = GRASS_Y_SUP_START; y < GRASS_Y_SUP_END; y++){
        mvwhline(game, y, 0, ' ', COLS);
    }
    attroff(COLOR_PAIR(COLOR_GRASS_ID));

    // River
    attron(COLOR_PAIR(COLOR_RIVER_ID));
    for (int y = RIVER_Y_START; y < RIVER_Y_END; y++){
        mvwhline(game, y, 0, ' ', COLS);
    }
    attroff(COLOR_PAIR(COLOR_RIVER_ID));

    // Bottom edge
    attron(COLOR_PAIR(COLOR_GRASS_ID));
    for (int y = GRASS_Y_INF_START; y < GRASS_Y_INF_END; y++){
        mvwhline(game, y, 0, ' ', COLS);
    }
    attroff(COLOR_PAIR(COLOR_GRASS_ID));
}

void print_frog(WINDOW *game, Character frog_entity){
    // Defined Frog Sprite
    static const char* frog[4][6]={
       {"","","▖","▗", "", ""},
       {"", "", "▟", "▀", "▙", ""},
       {"▝", "▟", "▀", "▀", "▙", "▘"},
    };

    attron(COLOR_PAIR(COLOR_FROG_ID));
    for (int i = 0; i < FROG_DIM_Y; i++)
    {
        for (int j = 0; j < FROG_DIM_X; j++)
        {
            if (i==0)
            {
                attron(COLOR_PAIR(COLOR_EYE_ID));
                mvwprintw(game, frog_entity.x, frog_entity.y,"%s",frog[i][j]);
                attroff(COLOR_PAIR(COLOR_EYE_ID));
                continue;
            }
            else if(i==2 && (j==0  || j==1 ||  j==4 || j==5))
            {
                attron(COLOR_PAIR(COLOR_LEGS_ID));
                mvwprintw(game, frog_entity.x, frog_entity.y + 1,"%s",frog[i][j]);
                attroff(COLOR_PAIR(COLOR_LEGS_ID));
                continue;
            }
            mvwprintw(game, frog_entity.x, frog_entity.y + 2, "%s",frog[i][j]);
        }
    }
    attroff(COLOR_PAIR(COLOR_FROG_ID));
}