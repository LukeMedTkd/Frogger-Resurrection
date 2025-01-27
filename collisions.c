#include "struct.h"
#include "entity.h"

void dens_collision(Character *Entities, Game_var *gameVar, bool *manche_ended){
    // 1 DENS - INSIDE
    if((Entities[FROG_ID].y == 1) && (Entities[FROG_ID].x == DENS1_START)){ 
        gameVar->dens[0] = FALSE;
        // TO DO: update score
    }
    // 1 DENS - OUTSIDE
    else if((Entities[FROG_ID].y == 1) && ((Entities[FROG_ID].x >= 0) && (Entities[FROG_ID].x < DENS1_START))) gameVar->lifes--;


    // 2 DENS - INSIDE
    if((Entities[FROG_ID].y == 1) && (Entities[FROG_ID].x == DENS2_START)){ 
        gameVar->dens[1] = FALSE;
        // TO DO: update score
    }
    // 2 DENS - OUTSIDE
    else if((Entities[FROG_ID].y == 1) && ((Entities[FROG_ID].x >= 0) && (Entities[FROG_ID].x < DENS1_START))) gameVar->lifes--;


    // 3 DENS - INSIDE
    if((Entities[FROG_ID].y == 1) && (Entities[FROG_ID].x == DENS3_START)){ 
        gameVar->dens[2] = FALSE;
        // TO DO: update score
    }
    // 3 DENS - OUTSIDE
    else if((Entities[FROG_ID].y == 1) && ((Entities[FROG_ID].x >= 0) && (Entities[FROG_ID].x < DENS3_START))) gameVar->lifes--;


    // 4 DENS - INSIDE
    if((Entities[FROG_ID].y == 1) && (Entities[FROG_ID].x == DENS4_START)){ 
        gameVar->dens[3] = FALSE;
        // TO DO: update score
    }
    // 4 DENS - OUTSIDE
    else if((Entities[FROG_ID].y == 1) && ((Entities[FROG_ID].x >= 0) && (Entities[FROG_ID].x < DENS4_START))) gameVar->lifes--;

    // 5 DENS - INSIDE
    if((Entities[FROG_ID].y == 1) && (Entities[FROG_ID].x == DENS5_START)){ 
        gameVar->dens[4] = FALSE;
        // TO DO: update score
    }
    // 5 DENS - OUTSIDE
    else if((Entities[FROG_ID].y == 1) && ((Entities[FROG_ID].x >= 0) && (Entities[FROG_ID].x < DENS5_START))) gameVar->lifes--;

    // Manche LOST
    //*(manche_ended) = TRUE;
}