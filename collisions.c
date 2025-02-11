#include "struct.h"
#include "entity.h"
#include "collisions.h"

void set_outcome(Game_var *gameVar, bool *manche_ended){
    // Set LOSER_OUTCOME to gameVar.outcome if manche == 0
    if(gameVar->manche == 0){
        gameVar->outcome = LOSER_OUTCOME;
        return;
    }

    // Set manche_ended = TRUE if time==0
    if(gameVar->time == 0){
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

void is_time_up(WINDOW *game, Character *Entities, Character * Bullets,  Game_var *gameVar, bool *manche_ended){
    if(gameVar->time == 0){
        gameVar->lifes--;
        gameVar->manche--;
        *manche_ended = TRUE;
        kill_threads(Entities, FIRST_CROCODILE, LAST_CROCODILE);
        wait_threads(Entities, FIRST_CROCODILE, LAST_CROCODILE);
        print_time_is_up(game);
    }
}

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
                gameVar->score += (100 * (gameVar->time)) / TIME;
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
}

// void generate_bullets(int *fds, Character *Entities, Character *Bullets, Game_var *gameVar, Msg *msg, int *random_shot, void (* crocodile_bullet_process)){

//     // If the CROCODILE is ready to shot
//     if(Bullets[msg->id].sig == DEACTIVE && *random_shot == 3 && gameVar->outcome == NO_OUTCOME){
//         int args[4] = {0};

//         // Get stream based on index
//             int n_stream = get_nStream_based_on_id(msg->id);

//         // Get the stream dir -> crocodile bullet orientation
//         int dir = (msg->x == 1 ? 1 : -1);

//         // Set args for crocodile bullet threads  -  args[4]:  | n_stream | stream_speed_with_dir | spawn delay | entity_id
//         args[1] = (abs(gameVar->streams_speed[n_stream]) - (abs(gameVar->streams_speed[n_stream]) * rand_range(MAX_BULLET_SPEED_INCREASE, MIN_BULLET_SPEED_INCREASE) / 100)) * dir;
//         args[2] = rand_range(MAX_BULLET_SPAWN, MIN_BULLET_SPAWN);
//         args[3] = msg->id + BULLET_OFFSET_ID;

//         // Create BULLET thread and run his routine
//         create_process(fds, Bullets, msg->id, msg->id + BULLET_OFFSET_ID, crocodile_bullet_process, args);

//         // Reset bullet position
//         reset_crocodile_bullet_position(Entities, Bullets, gameVar, msg->id);

//         Bullets[msg->id].sig = ACTIVE;

//     }
// }

void reset_bullets_signal(Character *Bullets){
    for(int i=0; i<N_BULLETS; i++){
        Bullets[i].sig = DEACTIVE;
        Bullets[i].tid = 0;
    }
}

// void deactive_bullets_out_game(Character *Bullets, int *current_bullet_id,  Msg *msg){
//     // If a RIGHT to LEFT bullet is ACTIVE but It's out of the GAME
//     if(Bullets[*current_bullet_id].sig == ACTIVE && Bullets[*current_bullet_id].x < 0 && msg->x == -1){
//             kill(Bullets[*current_bullet_id].pid, SIGKILL);
//             waitpid(Bullets[*current_bullet_id].pid, NULL, WNOHANG);
//             Bullets[*current_bullet_id].sig = DEACTIVE;
//     } 
    
//     // If a LEFT to RIGHT bullet is ACTIVE but It's out of the GAME
//     else if(Bullets[*current_bullet_id].sig == ACTIVE && Bullets[*current_bullet_id].x > GAME_WIDTH && msg->x == 1){
//         kill(Bullets[*current_bullet_id].pid, SIGKILL);
//         waitpid(Bullets[*current_bullet_id].pid, NULL, WNOHANG);
//         Bullets[*current_bullet_id].sig = DEACTIVE;
//     }
// }

// void frog_killed(Character *Entities, Character *Bullets, Game_var *gameVar, bool *manche_ended, int *current_bullet_id){

//     // Checks if BULLET.y MATCHS with FROG.y
//     if(Bullets[*current_bullet_id].sig == ACTIVE && (Bullets[*current_bullet_id].y > Entities[FROG_ID].y && Bullets[*current_bullet_id].y < Entities[FROG_ID].y + FROG_DIM_Y)){

//         // Checks if BULLET.x MATCHS with FROG.x
//         if(Bullets[*current_bullet_id].x == Entities[FROG_ID].x || Bullets[*current_bullet_id].x == Entities[FROG_ID].x + FROG_DIM_X - 1){
//             gameVar->lifes--;
//             gameVar->manche--;
//             *manche_ended = TRUE;
//             return;
//         }
//     }
// }

void bullets_collision(Character *Entities, Character *Bullets, Game_var *gameVar, bool *manche_ended){
    // If some crocodiles bullet is ACTIVE and the manche ends, the bullets are set to DEACTIVE and are killed
    for(int i = 0; i < N_BULLETS; i++){
        if(Bullets[i].sig == ACTIVE && *manche_ended){
            if(Bullets[i].tid != 0){
                pthread_cancel(Bullets[i].tid);
                pthread_join(Bullets[i].tid, NULL);
                Bullets[i].sig = DEACTIVE;
            }
        }
    }
}

//     // Checks if some FROG Bullets neutralize some CROCODILE Bullets
//     int current_crocodile_index, current_stream = 0;
//     if (RIVER_Y_START <= Entities[FROG_ID].y && Entities[FROG_ID].y < RIVER_Y_END) {
//         // Get index of the current stream
//         while ((CROCODILE_OFFSET_Y + (current_stream * CROCODILE_DIM_Y)) < Entities[FROG_ID].y) current_stream++;

//         // Check 3 crocodiles bullets at once
//         for (int j = 0; j < MAX_N_CROCODILE_PER_STREAM; j++) {
//             current_crocodile_index = FIRST_CROCODILE + (current_stream * MAX_N_CROCODILE_PER_STREAM) + j;

//             // Checks if BULLET.y MATCHS with FROG.y
//             if(Bullets[current_crocodile_index].sig == ACTIVE && 
//             (Bullets[current_crocodile_index].y > Entities[FROG_ID].y && 
//             Bullets[current_crocodile_index].y < Entities[FROG_ID].y + FROG_DIM_Y)){

//                 // Checks if a RIGHT to LEFT bullet is ACTIVE and RIGHT FROG bullet is ACTIVE and their x matching
//                 if(Bullets[current_crocodile_index].sig == ACTIVE && Bullets[FROG_ID+1].sig == ACTIVE && ((Bullets[current_crocodile_index].x - Bullets[FROG_ID+1].x >= -1) && (Bullets[current_crocodile_index].x - Bullets[FROG_ID+1].x <= 1))){
//                     kill(Bullets[FROG_ID+1].pid, SIGKILL);
//                     waitpid(Bullets[FROG_ID+1].pid, NULL, WNOHANG);
//                     Bullets[FROG_ID+1].sig = DEACTIVE;
                    
//                     kill(Bullets[current_crocodile_index].pid, SIGKILL);
//                     waitpid(Bullets[current_crocodile_index].pid, NULL, WNOHANG);
//                     Bullets[current_crocodile_index].sig = DEACTIVE;
//                 }

//                 // Checks if a LEFT to RIGHT bullet is ACTIVE and LEFT FROG bullet is ACTIVE and their x matching
//                 if(Bullets[current_crocodile_index].sig == ACTIVE && Bullets[FROG_ID].sig == ACTIVE && ((Bullets[current_crocodile_index].x - Bullets[FROG_ID].x >= -1) && (Bullets[current_crocodile_index].x - Bullets[FROG_ID].x <= 1))){
//                     kill(Bullets[FROG_ID].pid, SIGKILL);
//                     waitpid(Bullets[FROG_ID].pid, NULL, WNOHANG);
//                     Bullets[FROG_ID].sig = DEACTIVE;

//                     kill(Bullets[current_crocodile_index].pid, SIGKILL);
//                     waitpid(Bullets[current_crocodile_index].pid, NULL, WNOHANG);
//                     Bullets[current_crocodile_index].sig = DEACTIVE;
//                 }
//             }
//         }
//     }
// }

void frog_on_crocodile_collision(Character *Entities, Game_var *gameVar, bool *manche_ended) {
    bool frog_on_crocodile = FALSE;
    static int last_crocodile_index, frog_offset_x, last_frog_x;
    int current_crocodile_index, direction, current_stream = 0;

    // Check if the FROG is on the RIVER area
    if (RIVER_Y_START <= Entities[FROG_ID].y && Entities[FROG_ID].y < RIVER_Y_END) {

        // Get index of the current stream
        while ((CROCODILE_OFFSET_Y + (current_stream * CROCODILE_DIM_Y)) < Entities[FROG_ID].y) current_stream++;
        // Get stream direction based on n_stream and frog.y
        direction = ((gameVar->streams_speed[current_stream] > 0) ? 1 : -1);

        // Check 3 crocodiles at once
        for (int j = 0; j < MAX_N_CROCODILE_PER_STREAM; j++) {
            current_crocodile_index = FIRST_CROCODILE + (current_stream * MAX_N_CROCODILE_PER_STREAM) + j;

            // Crocodiles from LEFT to RIGHT
            if (direction == 1) {
                // Check if the FROG is on the crocodile
                if ((Entities[FROG_ID].x >= (Entities[current_crocodile_index].x + CROCODILE_TAIL_OFFSET)) &&
                    ((Entities[FROG_ID].x <= (Entities[current_crocodile_index].x + CROCODILE_DIM_X - CROCODILE_HEAD_OFFSET - FROG_DIM_X)))) {
                    frog_on_crocodile = TRUE;
                    break;
                }
            }

            // Crocodiles from RIGHT to LEFT
            if (direction == -1) {
                // Check if the FROG is on the crocodile
                if ((Entities[FROG_ID].x >= (Entities[current_crocodile_index].x + CROCODILE_HEAD_OFFSET)) &&
                    ((Entities[FROG_ID].x <= (Entities[current_crocodile_index].x + CROCODILE_DIM_X - CROCODILE_TAIL_OFFSET - FROG_DIM_X)))) {
                    frog_on_crocodile = TRUE;
                    break;
                }
            }
        }

        // Checks if the FROG has fallen on the river -> She lose 1 life and 1 manche
        if(frog_on_crocodile == FALSE) {
            gameVar->manche--;
            gameVar->lifes--;
            *manche_ended = TRUE;
            return;
        } 
        
        // frog_on_crocodile == TRUE
        else {
            
            // Checks if the FROG has changed crocodile
            if (current_crocodile_index != last_crocodile_index) {
                // Compute the FROG offset between the previous crocodile and the current one and update the last_crocodile_index
                frog_offset_x = Entities[FROG_ID].x - Entities[current_crocodile_index].x;
                last_crocodile_index = current_crocodile_index;  
            }

            // If the FROG is moving, update the frog_offset_x
            if (Entities[FROG_ID].x != last_frog_x) 
                frog_offset_x = Entities[FROG_ID].x - Entities[current_crocodile_index].x;    

            // If the FROG is NOT moving - CHECK if the FROG is in the game area
            else if(Entities[FROG_ID].x >= 0 && Entities[FROG_ID].x <= (GAME_WIDTH - FROG_DIM_X))
                Entities[FROG_ID].x = Entities[current_crocodile_index].x + frog_offset_x;

            // Store the last FROG position
            last_frog_x = Entities[FROG_ID].x;

            // Checks if the FROG is in the crocodile area
            if (direction == 1) {
                if (Entities[FROG_ID].x < Entities[current_crocodile_index].x + CROCODILE_TAIL_OFFSET) 
                    Entities[FROG_ID].x = Entities[current_crocodile_index].x + CROCODILE_TAIL_OFFSET;

                else if (Entities[FROG_ID].x > Entities[current_crocodile_index].x + CROCODILE_DIM_X - CROCODILE_HEAD_OFFSET - FROG_DIM_X)
                    Entities[FROG_ID].x = Entities[current_crocodile_index].x + CROCODILE_DIM_X - CROCODILE_HEAD_OFFSET - FROG_DIM_X;

            } 
            
            else if (direction == -1) {
                if (Entities[FROG_ID].x < Entities[current_crocodile_index].x + CROCODILE_HEAD_OFFSET)
                    Entities[FROG_ID].x = Entities[current_crocodile_index].x + CROCODILE_HEAD_OFFSET;

                else if (Entities[FROG_ID].x > Entities[current_crocodile_index].x + CROCODILE_DIM_X - CROCODILE_TAIL_OFFSET - FROG_DIM_X)
                    Entities[FROG_ID].x = Entities[current_crocodile_index].x + CROCODILE_DIM_X - CROCODILE_TAIL_OFFSET - FROG_DIM_X;
            }
        }
    }
}
