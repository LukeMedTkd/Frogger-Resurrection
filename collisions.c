#include "struct.h"
#include "entity.h"

void dens_collision(Character *Entities, Game_var *gameVar, Msg msg, bool *manche_ended){

    // 1 DENS - INSIDE
    if((Entities[FROG_ID].y == 1) && (Entities[FROG_ID].x == DENS1_START)){ 
        if (gameVar->dens[0] ==  FALSE){ //Tana già chiusa-> MANCHE PERSA!
            gameVar->lifes--;
            gameVar->manche--;
            //Manche LOST
            *(manche_ended) = TRUE;
        }
        else{
            gameVar->dens[0] = FALSE;//
            gameVar->score += (100 * (TIME - gameVar->time)) / TIME;
            // Manche WON
            *(manche_ended) = TRUE;
        }
    }
    // 1 DENS - OUTSIDE
    else if((Entities[FROG_ID].y == 1) && ((Entities[FROG_ID].x >= 0) && (Entities[FROG_ID].x < DENS1_START))){
        (*gameVar).lifes--;
        gameVar->manche--;
        // Manche LOST
        *(manche_ended) = TRUE;
    }

    /*-----------------------------------------------------------------------------------------------------------------*/

    // 2 DENS - INSIDE
    if((Entities[FROG_ID].y == 1) && (Entities[FROG_ID].x == DENS2_START)){ 
        if (gameVar->dens[1] ==  FALSE){//Tana già chiusa-> MANCHE PERSA!
            gameVar->lifes--;
            gameVar->manche--;
            // Manche LOST
            *(manche_ended) = TRUE;
        }
        else{
            gameVar->dens[1] = FALSE;//
            gameVar->score += (100 * (TIME - gameVar->time)) / TIME;
            // Manche WON
            *(manche_ended) = TRUE;
        }
    }
    // 2 DENS - OUTSIDE
    else if((Entities[FROG_ID].y == 1) && ((Entities[FROG_ID].x >= (DENS1_START + 1)) && (Entities[FROG_ID].x < DENS2_START))){
        gameVar->lifes--;
        gameVar->manche--;
        // Manche LOST
        *(manche_ended) = TRUE;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/

    // 3 DENS - INSIDE
    if((Entities[FROG_ID].y == 1) && (Entities[FROG_ID].x == DENS3_START)){ 
        if (gameVar->dens[2] ==  FALSE){//Tana già chiusa-> MANCHE PERSA!
            gameVar->lifes--;
            gameVar->manche--;
            // Manche LOST
            *(manche_ended) = TRUE;
        }
        else{
            gameVar->dens[2] = FALSE;//
            gameVar->score += (100 * (TIME - gameVar->time)) / TIME;
            // Manche WON
            *(manche_ended) = TRUE;
        }
    }
    // 3 DENS - OUTSIDE
    else if((Entities[FROG_ID].y == 1) && ((Entities[FROG_ID].x >= (DENS2_START + 1) && (Entities[FROG_ID].x < DENS3_START)))){
        gameVar->lifes--;
        gameVar->manche--;
        // Manche LOST
        *(manche_ended) = TRUE;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/

    // 4 DENS - INSIDE
    if((Entities[FROG_ID].y == 1) && (Entities[FROG_ID].x == DENS4_START)){ 
        if (gameVar->dens[3] ==  FALSE){//Tana già chiusa-> MANCHE PERSA!
            gameVar->lifes--;
            gameVar->manche--;
            // Manche LOST
            *(manche_ended) = TRUE;
        }
        else{
            gameVar->dens[3] = FALSE;//
            gameVar->score += (100 * (TIME - gameVar->time)) / TIME;
            // Manche WON
            *(manche_ended) = TRUE;
        }
    }
    // 4 DENS - OUTSIDE
    else if((Entities[FROG_ID].y == 1) && ((Entities[FROG_ID].x >= (DENS3_START + 1)) && (Entities[FROG_ID].x < DENS4_START))){
        gameVar->lifes--;
        gameVar->manche--;
        // Manche LOST
        *(manche_ended) = TRUE;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/

    // 5 DENS - INSIDE
    if((Entities[FROG_ID].y == 1) && (Entities[FROG_ID].x == DENS5_START)){ 
        if (gameVar->dens[4] ==  FALSE){//Tana già chiusa-> MANCHE PERSA!
            gameVar->lifes--;
            gameVar->manche--;
            // Manche LOST
            *(manche_ended) = TRUE;
        }
        else{
            gameVar->dens[4] = FALSE;//
            gameVar->score += (100 * (TIME - gameVar->time)) / TIME;
            // Manche WON
            *(manche_ended) = TRUE;
        }
    }
    // 5 DENS - OUTSIDE
    else if((Entities[FROG_ID].y == 1) && ((Entities[FROG_ID].x >= (DENS4_START + 1)) && (Entities[FROG_ID].x < DENS5_START))){
        gameVar->lifes--;
        gameVar->manche--;
        // Manche LOST
        *(manche_ended) = TRUE;
    }
    // 5 DENS - OUTSIDE
    else if((Entities[FROG_ID].y == 1) && ((Entities[FROG_ID].x >= (DENS5_START + 1)) && (Entities[FROG_ID].x < GAME_WIDTH))){
        gameVar->lifes--;
        gameVar->manche--;
        // Manche LOST
        *(manche_ended) = TRUE;
    }
}

void frog_collision(Character *Entities, Game_var *gameVar, Msg msg, bool *manche_ended){

    //FROG falls into the RIVER
    bool frog_on_crocodile = FALSE;
    if (Entities[FROG_ID].y < GRASS_Y_INF_START && Entities[FROG_ID].y > RIVER_Y_START){
        for (int i = FIRST_CROCODILLE; i < LAST_CROCODILLE; i++){
            if ((Entities[FROG_ID].y == Entities[i].y) && ((Entities[FROG_ID].x >= (Entities[i].x + FROG_DIM_X)) && (Entities[FROG_ID].x <= (Entities[i].x) + (FROG_DIM_X * 2)))){
            frog_on_crocodile = TRUE;
            //Entities[FROG_ID].y = Entities[i].y;
            //Entities[FROG_ID].x = Entities[i].x;
            break;

            //TO DO: gestire rana sopra il coccodirllo
            } 
        }
        if(!frog_on_crocodile) gameVar->lifes--, *(manche_ended) = TRUE;
    }
}
