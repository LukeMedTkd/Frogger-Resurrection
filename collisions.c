#include "struct.h"
#include "entity.h"

void dens_collision(Character *Entities, Game_var *gameVar, bool *manche_ended){

    int dens_start[] = {DENS1_START, DENS2_START, DENS3_START, DENS4_START, DENS5_START};

    for (int i = 0; i < N_DENS; i++){
        // Legal AREA
        if((Entities[FROG_ID].y == 1) && (Entities[FROG_ID].x == dens_start[i])){ 
            // The den already close: lost manche
            if (gameVar->dens[i] ==  FALSE){ 
                gameVar->lifes--;
                gameVar->manche--;
            }
            // The den is still open: update the score
            else{
                gameVar->dens[i] = FALSE;
                gameVar->score += (100 * (TIME - gameVar->time)) / TIME;
            }
            *(manche_ended) = TRUE;
        }

    }

    // Illegal AREA
    if(Entities[FROG_ID].y == 1){
        // FROG on the dens' edges
        if (Entities[FROG_ID].x < dens_start[0] || Entities[FROG_ID].x > dens_start[N_DENS - 1]) {
            gameVar->lifes--;
            gameVar->manche--;
            *manche_ended = TRUE;
        } 
        
        // FROG between two dens
        else{
            for (int i = 0; i < N_DENS - 1; i++) {
                if (Entities[FROG_ID].x > dens_start[i] && Entities[FROG_ID].x < dens_start[i + 1]) {
                    gameVar->lifes--;
                    gameVar->manche--;
                    *manche_ended = TRUE;
                }
            }
        }
    }
    

    // Set LOSER_OUTCOME to gameVar.outcome if manche == 0
    if(gameVar->manche == 0){
        gameVar->outcome = LOSER_OUTCOME;
        return;
    }

    // Set TIME_IS_UP_OUTCOME to gameVar.outcome if gameVar.time == 0
    if(gameVar->time == 0){
        gameVar->outcome = TIME_IS_UP_OUTCOME;
        *manche_ended = TRUE;
        return;
    }

    // Set WINNER_OUTCOME to gameVar.outcome if gameVar.dens[all] == FALSE
    for(int i = 0; i < N_DENS; i++){
        if (gameVar->dens[i] == TRUE){
            gameVar->outcome = NO_OUTCOME;
            return;
        }
    }
    gameVar->outcome = WINNER_OUTCOME;
    *manche_ended = TRUE;
}


void frog_collision(Character *Entities, Game_var *gameVar, Msg msg, bool *manche_ended){

    //FROG falls into the RIVER
    bool frog_on_crocodile = FALSE;
    if (Entities[FROG_ID].y < GRASS_Y_INF_START && Entities[FROG_ID].y > RIVER_Y_START){
        for (int i = FIRST_CROCODILE; i < LAST_CROCODILE; i++){
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
