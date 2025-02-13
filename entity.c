#include "entity.h"
#include "struct.h"
#include "game.h"
#include "sprites.h"
#include "collisions.h"
#include "utils.h"

extern Buffer buf;

/*--------------------------------------------------*/
/*------------------ Frog Entity -------------------*/
void *frog_thread(void *args){

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
            write_msg(&buf, msg); // Write message on buffer

            // Reset Defaults
            direction = 1;
            msg.id = FROG_ID;
            msg.sig = FROG_POSITION_SIG;
            msg_to_send= FALSE;
        }
    }
}

void *left_frog_bullet_thread(void *args){

    Msg msg;
    msg.x = -1;
    msg.id = LEFT_FROG_BULLET_ID;

    while(TRUE){
        write_msg(&buf, msg);
        usleep(FROG_BULLET_SPEED);
    }
}

void *right_frog_bullet_thread(void *args){

    Msg msg;
    msg.x = 1;
    msg.id = RIGHT_FROG_BULLET_ID;

    while(TRUE){
        write_msg(&buf, msg);
        usleep(FROG_BULLET_SPEED);
    }
}

void reset_frog_position(Character *frog_entity){
    frog_entity->y = FROG_INIT_Y;
    frog_entity->x = FROG_INIT_X;
}

void reset_frog_bullet_position(Character *Entities, Character *Bullets){
    Bullets[FROG_ID].x = Entities[FROG_ID].x;
    Bullets[FROG_ID].y = Entities[FROG_ID].y + (FROG_DIM_Y / 2);
    Bullets[FROG_ID + 1].x = Entities[FROG_ID].x + FROG_DIM_X - 1;
    Bullets[FROG_ID + 1].y = Entities[FROG_ID].y + (FROG_DIM_Y / 2);
}

/*-------------------------------------------------------*/
/*------------------ Crocodile Entity -------------------*/
void *crocodile_thread(void* args){

    int *arg = (void *)args;

    // The spawn delay based on crocodile_id
    int stream_speed = abs(arg[1]);
    int spawn_delay = arg[2];  

    // Get direction through the stream speed     args[4]:  | n_stream | stream_speed_with_dir | spawn delay | entity_id
    int direction = (arg[1] > 0 ? 1 : -1);

    // Declare msg and Set attr
    Msg msg;
    msg.id = arg[3];
    msg.x = CROCODILE_MOVE_X * direction;
    msg.y = 0;

    // The spawn time is delayed
    usleep(spawn_delay);

    while (TRUE){
        write_msg(&buf, msg);
        usleep(stream_speed);
    }

    free(args);
    
}

void *crocodile_bullet_thred(int* args){
    // args[4]:  | n_stream | stream_speed_with_dir | spawn delay | entity_id
    Msg msg;
    msg.x = (args[1] > 0 ? 1 : -1);
    msg.id = args[3];
    
    usleep(abs(args[2]));
    while(TRUE){
        write_msg(&buf, msg);
        usleep(abs(args[1]));
    } 
}

void reset_crocodile_position(Character *crocodile_entity, int n_stream, Game_var *gameVar){
    // Determine the correct position: set crocodile_init_x, crocodile_init_y
    crocodile_entity->y = (CROCODILE_OFFSET_Y) + (n_stream * CROCODILE_DIM_Y);
    crocodile_entity->x = (gameVar->streams_speed[n_stream] > 0 ? (-CROCODILE_DIM_X - 1) : (GAME_WIDTH + 1));
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
void *timer_thread(void *args){

    Msg msg;
    msg.x = -1;
    msg.id = TIME_ID;

    while(TRUE){
        write_msg(&buf, msg);
        sleep(1);
    }
}

void reset_timer(Game_var *gameVar){
    gameVar->time = TIME;
}


/*--------------------------------------------------------*/
/*-------------------- Parent thread --------------------*/
void parent_thread(WINDOW *game, WINDOW *score, Buffer *buf, Character *Entities, Character *Bullets, Game_var *gameVar){

    int current_bullet_id, random_shot = -1; // Crocodiles utils variables
    bool manche_ended = FALSE; // Flag
    Msg msg; // Define msg to store buffer message

    // Manche Loop
    while(!manche_ended){

        // Read msg from the buffer
        msg = read_msg(buf);

        switch (msg.id){
            
            // ************************** 
            // Msg from FROG thread
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

                        // Create BULLETS threads and run their routine
                        create_thread(Bullets, FROG_ID, LEFT_FROG_BULLET_ID, left_frog_bullet_thread, NULL);
                        create_thread(Bullets, FROG_ID + 1, RIGHT_FROG_BULLET_ID, right_frog_bullet_thread, NULL);
                    }
                }
                break;


            // ***********************************
            // Msg from some FROG BULLET thread
            // ***********************************
            case LEFT_FROG_BULLET_ID:

                // Set LEFT Bullet SIG
                Bullets[FROG_ID].sig = ((Bullets[FROG_ID].x >= 0) ? ACTIVE : DEACTIVE);

                // If LEFT bullet is ACTIVE
                if(Bullets[FROG_ID].sig == ACTIVE) Bullets[FROG_ID].x += msg.x;

                // If LEFT bullet is DEACTIVE
                else{ 
                    pthread_cancel(Bullets[FROG_ID].tid);
                    pthread_join(Bullets[FROG_ID].tid, NULL);
                }
                
                
                break;


            case RIGHT_FROG_BULLET_ID:

                // Set RIGHT Bullet SIG
                Bullets[FROG_ID + 1].sig = ((Bullets[FROG_ID + 1].x <= GAME_WIDTH) ? ACTIVE : DEACTIVE);

                // If RIGHT bullet is ACTIVE
                if(Bullets[FROG_ID + 1].sig == ACTIVE) Bullets[FROG_ID + 1].x += msg.x;

                // If RIGHT bullet is DEACTIVE
                else{ 
                    pthread_cancel(Bullets[FROG_ID + 1].tid);
                    pthread_join(Bullets[FROG_ID + 1].tid, NULL);
                }

                break;


            // ************************************ 
            // Msg from some CROCODILE threads
            // ************************************  
            case FIRST_CROCODILE ... LAST_CROCODILE:

                // Check if this crocodille is ONLINE or is OFFLINE
                Entities[msg.id].sig = ((Entities[msg.id].x + msg.x > GAME_WIDTH) || (Entities[msg.id].x + msg.x < -CROCODILE_DIM_X) ? CROCODILE_OFFLINE : CROCODILE_ONLINE);

                // Generate a random_shot value
                random_shot = rand_range(MAX_RANDOM_SHOT, MIN_RANDOM_SHOT);

                // Updates the crocodile position only if the crocodile signal is ONLINE, else resets crocodile positin
                if(Entities[msg.id].sig == CROCODILE_ONLINE){
                    Entities[msg.id].x += msg.x;
                    
                    // If the crocodile is ONLINE, It can shot - The crocodile shot based on random_shot VALUE
                    //generate_bullets(Entities, Bullets, gameVar, &msg, &random_shot, crocodile_bullet_thred); 
                }

                else{
                    // If some crocodile is OFFLINE -> reset his position
                    reset_crocodile_position(&(Entities[msg.id]), get_nStream_based_on_id(msg.id), gameVar);
                }
                break;

            // ************************************ 
            // Msg from some CROCODILE BULLETS threads
            // ************************************  
            case (FIRST_CROCODILE + BULLET_OFFSET_ID) ... (LAST_CROCODILE + BULLET_OFFSET_ID):
                
                // Current Bullet id
                current_bullet_id = msg.id - BULLET_OFFSET_ID;

                // If bullet is ACTIVE
                if(Bullets[current_bullet_id ].sig == ACTIVE) Bullets[current_bullet_id ].x += msg.x;

                // Check if a bullet is out of the GAME
                deactive_bullets_out_game(Bullets, &current_bullet_id, &msg);

                // Checks if some CROCODILE BULLETS kill the FROG
                frog_killed(Entities, Bullets, gameVar, &manche_ended, &current_bullet_id);


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
        frog_on_crocodile_collision(Entities, gameVar, &manche_ended);
        is_time_up(game, Entities, Bullets, gameVar, &manche_ended);
        bullets_collision(Entities, Bullets, gameVar, &manche_ended);
        set_outcome(gameVar, &manche_ended);
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