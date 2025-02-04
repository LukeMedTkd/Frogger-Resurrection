#include "entity.h"
#include "struct.h"
#include "game.h"
#include "sprites.h"
#include "collisions.h"
#include "utils.h"

/*--------------------------------------------------*/
/*------------------ Frog Entity -------------------*/
void frog_process(int pipe_write, int* args){

    // Init some variables
    int move, direction = 1;
    bool msg_to_send = TRUE; // avoid writing no movements

    // Declare msg and attr
    Msg msg;
    msg.sig = FROG_POSITION_SIG; // Set the message signal to move the frog
    msg.y = 0;
    msg.x = 0;

    while(TRUE){
        move = getch();
        switch(move){
            case KEY_UP:
                direction = -1;
            case KEY_DOWN:
                msg.y = FROG_MOVE_Y * direction;
                msg.x = 0;
                msg_to_send = TRUE;
                break;
            case KEY_LEFT:
                direction = -1;
            case KEY_RIGHT:
                msg.x = FROG_MOVE_X * direction;
                msg.y = 0;
                msg_to_send = TRUE;
                break;
            case KEY_SHOT:
                msg.sig = FROG_SHOT_SIG; // Change the message signal to shot a bullet
                msg_to_send = TRUE; // Set flag to send msg
                break;
            default: break; 
        }

        // Check if a message needs to be sent
        if(msg_to_send) {
            write_msg(pipe_write, msg); // Write message on pipe

            // Reset Defaults
            direction = 1;
            msg.id = FROG_ID;
            msg.sig = FROG_POSITION_SIG;
            msg_to_send= FALSE;
        }
    }
}

void reset_frog_position(Character *frog_entity){
    frog_entity->y = FROG_INIT_Y;
    frog_entity->x = FROG_INIT_X;
}

void left_frog_bullet_process(int pipe_write, int* args){
    Msg msg;
    msg.x = -1;
    msg.id = LEFT_FROG_BULLET_ID;

    while(TRUE){
        write_msg(pipe_write, msg);
        usleep(MAX_BULLET_SPEED);
    }
}

void right_frog_bullet_process(int pipe_write, int* args){
    Msg msg;
    msg.x = 1;
    msg.id = RIGHT_FROG_BULLET_ID;

    while(TRUE){
        write_msg(pipe_write, msg);
        usleep(MAX_BULLET_SPEED);
    }    
}

void reset_frog_bullet_position(Character *Entities, Character *Bullets){
    Bullets[FROG_ID].x = Entities[FROG_ID].x;
    Bullets[FROG_ID].y = Entities[FROG_ID].y + (FROG_DIM_Y / 2);
    Bullets[FROG_ID + 1].x = Entities[FROG_ID].x + FROG_DIM_X - 1;
    Bullets[FROG_ID + 1].y = Entities[FROG_ID].y + (FROG_DIM_Y / 2);
}

/*-------------------------------------------------------*/
/*------------------ Crocodile Entity -------------------*/
void crocodile_process(int pipe_write, int* args){

    // The spawn delay based on crocodile_id
    int stream_speed = abs(args[1]), spawn_delay = args[2]; 

    // Get direction through the stream speed     args[4]:  | n_stream | stream_speed_with_dir | spawn delay | entity_id
    int direction = (args[1] > 0 ? 1 : -1);

    // Declare msg and Set attr
    Msg msg;
    msg.id = args[3];
    msg.x = CROCODILE_MOVE_X * direction;
    msg.y = 0;


    // The spawn time is delayed
    usleep(spawn_delay);

    while (TRUE){
        write_msg(pipe_write, msg);
        usleep(stream_speed);
    }
    
}

void reset_crocodile_position(Character *crocodile_entity, int n_stream, Game_var *gameVar){
    // Determine the correct position: set crocodile_init_x, crocodile_init_y
    crocodile_entity->y = (CROCODILE_OFFSET_Y) + (n_stream * CROCODILE_DIM_Y);
    crocodile_entity->x = (gameVar->streams_speed[n_stream] > 0 ? (-CROCODILE_DIM_X - 1) : (GAME_WIDTH + 1));
}

void crocodile_bullet_process(int pipe_write, int* args){
    // args[4]:  | n_stream | stream_speed_with_dir | spawn delay | entity_id
    Msg msg;
    msg.x = (args[1] > 0 ? 1 : -1);
    msg.id = args[3];
    
    while(TRUE){
        write_msg(pipe_write, msg);
        usleep(abs(args[1]));
    } 
}

void reset_crocodile_bullet_position(Character *Entities, Character *Bullets, Game_var *gameVar, int index){
    // Get stream based on index
    int n_stream = get_nStream_based_on_id(index);

    // Get the stream dir -> crocodile orientation
    int dir = (gameVar->streams_speed[n_stream] > 0 ? 1 : -1);

    // Reset the correct crocodile bullet position
    Bullets[index].x = (dir == 1 ? (Entities[index].x + CROCODILE_DIM_X - 1) : (Entities[index].x + 1));
    Bullets[index].y = Entities[index].y + (CROCODILE_DIM_Y / 2);
}

/*---------------------------------------------------*/
/*------------------ Timer Entity -------------------*/
void reset_timer(Game_var *gameVar){
    gameVar->time = TIME;
}

void timer_process(int pipe_write, int* args){
    Msg msg;
    msg.x = -1;
    msg.id = TIME_ID;

    while(TRUE){
        write_msg(pipe_write,msg);
        sleep(1);
    }
}


/*--------------------------------------------------------*/
/*-------------------- Parent Process --------------------*/
void parent_process(WINDOW *game, WINDOW *score, int *fds, Character *Entities, Character *Bullets, Game_var *gameVar){

    bool manche_ended = FALSE; // Flag
    Msg msg; // Define msg to store pipe message

    // Manche Loop
    while(!manche_ended){
        
        // Read msg from the pipes
        msg = read_msg(fds[PIPE_READ]);

        switch (msg.id){
            
            // ************************** 
            // Msg from FROG process
            // **************************
            case FROG_ID:

                // FROG has moved - Update POSITION
                if(msg.sig == FROG_POSITION_SIG){
                    Entities[FROG_ID].y += ((Entities[FROG_ID].y + msg.y >= 0) && (Entities[FROG_ID].y + msg.y < GAME_HEIGHT)) ? msg.y : 0;
                    Entities[FROG_ID].x += ((Entities[FROG_ID].x + msg.x >= 0) && (Entities[FROG_ID].x + FROG_DIM_X + msg.x <= GAME_WIDTH)) ? msg.x : 0;
                }

                // FROG has shotted
                if(msg.sig == FROG_SHOT_SIG){

                    if(Bullets[FROG_ID].sig == DEACTIVE && Bullets[FROG_ID+1].sig == DEACTIVE){

                        // Initialize the bullets position
                        reset_frog_bullet_position(Entities, Bullets);
                        
                        // Create BULLETS processes and run their routine
                        create_process(fds, Bullets, FROG_ID, LEFT_FROG_BULLET_ID, &left_frog_bullet_process, NULL);
                        create_process(fds, Bullets, FROG_ID + 1, RIGHT_FROG_BULLET_ID, &right_frog_bullet_process, NULL);
                    }
                }
                break;


            // ***********************************
            // Msg from some FROG BULLET process
            // ***********************************
            case LEFT_FROG_BULLET_ID:
                // Set LEFT Bullet SIG
                Bullets[FROG_ID].sig = ((Bullets[FROG_ID].x >= 0) ? ACTIVE : DEACTIVE);

                // If LEFT bullet is ACTIVE
                if(Bullets[FROG_ID].sig == ACTIVE) Bullets[FROG_ID].x += msg.x;

                // If LEFT bullet is DEACTIVE
                else{ 
                    kill(Bullets[FROG_ID].pid, SIGKILL);
                    waitpid(Bullets[FROG_ID].pid, NULL, WNOHANG);
                }
                
                break;


            case RIGHT_FROG_BULLET_ID:
                // Set RIGHT Bullet SIG
                Bullets[FROG_ID + 1].sig = ((Bullets[FROG_ID + 1].x <= GAME_WIDTH) ? ACTIVE : DEACTIVE);

                // If RIGHT bullet is ACTIVE
                if(Bullets[FROG_ID + 1].sig == ACTIVE) Bullets[FROG_ID + 1].x += msg.x;

                // If RIGHT bullet is DEACTIVE
                else{ 
                    kill(Bullets[FROG_ID + 1].pid, SIGKILL);
                    waitpid(Bullets[FROG_ID + 1].pid, NULL, WNOHANG);
                }

                break;


            // ************************************ 
            // Msg from some CROCODILE processes
            // ************************************  
            case FIRST_CROCODILE ... LAST_CROCODILE:
                // Check if this crocodille is online or is offline
                Entities[msg.id].sig = ((Entities[msg.id].x + msg.x > GAME_WIDTH) || (Entities[msg.id].x + msg.x < -CROCODILE_DIM_X) ? CROCODILE_OFFLINE : CROCODILE_ONLINE);

                // Update the crocodile position only if the crocodile signal is ONLINE, else reset crocodile positin
                if(Entities[msg.id].sig == CROCODILE_ONLINE){
                    Entities[msg.id].x += msg.x;  
                }

                else{
                    // If some crocodile is OFFLINE -> reset his position
                    reset_crocodile_position(&(Entities[msg.id]), get_nStream_based_on_id(msg.id), gameVar);
                }
                break;

            // ************************************ 
            // Msg from some CROCODILE processes
            // ************************************  
            case (FIRST_CROCODILE + BULLET_OFFSET_ID) ... (LAST_CROCODILE + BULLET_OFFSET_ID):
                // Set Bullet SIG
                Bullets[msg.id - BULLET_OFFSET_ID].sig = ((Bullets[msg.id - BULLET_OFFSET_ID].x > 0 || Bullets[msg.id - BULLET_OFFSET_ID].x < GAME_WIDTH) ? ACTIVE : DEACTIVE);

                // If bullet is ACTIVE
                if(Bullets[msg.id - BULLET_OFFSET_ID].sig == ACTIVE) Bullets[msg.id - BULLET_OFFSET_ID].x += msg.x;

                // If bullet is DEACTIVE
                else{
                    kill(Bullets[msg.id - BULLET_OFFSET_ID].pid, SIGKILL);
                    waitpid(Bullets[msg.id - BULLET_OFFSET_ID].pid, NULL, WNOHANG);
                }
                break;
            


            // ************************** 
            // Msg from TIME
            // **************************
            case TIME_ID:
                gameVar->time += msg.x;
        

            default:
                break;
        }

        /*------------------------ Check some collisions ----------------------*/
        // Check all the dens
        dens_collision(Entities, gameVar, &manche_ended);
        //frog_on_crocodile_collision(Entities, gameVar, &manche_ended);
        is_time_up(game, Entities, Bullets, gameVar, &manche_ended);
        frog_bullets_collision(Entities, Bullets, &manche_ended);  
        crocodile_bullets_collsion(Entities, Bullets, &manche_ended);
        set_outcome(gameVar, &manche_ended);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        int crocodile_ready_to_shot, n_fired_bullets = 0, fired_bullets[N_BULLETS], args[4] = {0};

        // Generate 3 new bullets if this condition is true
        if(gameVar->n_max_bullets > 0){
            
            // Generate random index
            crocodile_ready_to_shot = rand_range(LAST_CROCODILE, FIRST_CROCODILE);

            // Checks if 'crocodile_ready_to_shot' it's not in the bullets_fired array yet and if the crocodile is in the game area
            if((!already_generated(crocodile_ready_to_shot, fired_bullets, N_MAX_BULLETS)) && Entities[crocodile_ready_to_shot].x > 0 && Entities[crocodile_ready_to_shot].x < GAME_HEIGHT - CROCODILE_DIM_X){
                fired_bullets[n_fired_bullets] = crocodile_ready_to_shot;
                n_fired_bullets++;

                // Reset bullet position
                reset_crocodile_bullet_position(Entities, Bullets, gameVar, crocodile_ready_to_shot);

                // Get stream based on index
                int n_stream = get_nStream_based_on_id(crocodile_ready_to_shot);
                // Get the stream dir -> crocodile bullet orientation
                int dir = (gameVar->streams_speed[n_stream] > 0 ? 1 : -1);

                // Set args for crocodile bullet process  -  args[4]:  | n_stream | stream_speed_with_dir | spawn delay | entity_id
                args[0] = n_stream; 
                args[1] = rand_range(MAX_BULLET_SPEED, MIN_BULLET_SPEED) * dir;
                args[2] = rand_range(MAX_SPAWN_TIME, MIN_SPAWN_TIME);
                args[3] = crocodile_ready_to_shot + BULLET_OFFSET_ID;

                // Create BULLET process and run his routine
                create_process(fds, Bullets, crocodile_ready_to_shot, crocodile_ready_to_shot + BULLET_OFFSET_ID, &crocodile_bullet_process, args);
                gameVar->n_max_bullets--;

            } // end if: condition to shot
        } // end if: n_max_bullets

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        /*------------------------ Update the scene --------------------------*/
        // Print Lifes
        print_lifes(score, gameVar->lifes);

        // Print Score
        print_score(score, gameVar->score);

        // Print Timer
        print_timer(score, gameVar->time);

        // Print Game Area
        print_game_area(game, gameVar->dens);

        // Print Crocodiles
        print_crocodiles(game, Entities, gameVar->streams_speed);

        // Print the Frog
        print_frog(game, Entities[FROG_ID]);

        // Print Frog Bullets
        print_frog_bullets(game, Bullets);

        // Print Crocodile Bullets
        print_crocodiles_bullets(game, Bullets);

        // Refresh the game and the score screen
        wrefresh(game);
        wrefresh(score);
    }
}