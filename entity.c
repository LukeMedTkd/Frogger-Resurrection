#include "entity.h"
#include "struct.h"
#include "game.h"
/*
1.frogProcess-> (pipe, *params)
2.Crocodile process-> (pipe, *params)
3.Bullet process-> (pipe, *params)
*/

void frog_process(int pipe_write, int* params){

    // Init some variables
    int move, direction = 1;
    bool msg_to_send = TRUE; // avoid writing no movements

    // Declare msg and attr
    Msg msg;
    msg.sig = FROG_POSITION_SIG; // Set message signal to move the frog
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
            case KEY_BACKSPACE:
                msg.sig = FROG_SHOT_SIG; // Change message signal to shot a bullet
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
    msg.sig = CROCODILE_ONLINE; // Set message signal to check if the crocodile is on game

    // The spawn time is delayed
    usleep(spawn_delay);

    while (TRUE){
        write_msg(pipe_write, msg);
        usleep(stream_speed);
    }
    
}

void reset_crocodile_position(Character *crocodile_entity, int* args){
    // Determine the correct position: set crocodile_init_x, crocodile_init_y
    crocodile_entity->y = (CROCODILE_OFFSET_Y) + ((args[0])*CROCODILE_DIM_Y);
    crocodile_entity->x = (args[1] > 0 ? (-CROCODILE_DIM_X) : (GAME_WIDTH));
}

void time_process(int pipe_write, int* params){
    
    while (TRUE){
        Msg msg;
        msg.x = *params;
        msg.id = TIME_ID;
        msg.y = 2;

        write_msg(pipe_write,msg);
        sleep(1);
    }
}

void parent_process(WINDOW *game, WINDOW *score,int pipe_read, Character *Entities, Game_var gameVar){
    bool manche_ended = FALSE; // Flag
    Msg msg; // Define msg to store pipe message

    // Manche Loop
    while(!manche_ended){

        // Read msg from the pipes
        msg = read_msg(pipe_read);

        switch (msg.id){
        
            // ************************** 
            // Msg from FROG
            // **************************
            case FROG_ID:

                // FROG has moved - Update POSITION
                if(msg.sig == FROG_POSITION_SIG){
                    Entities[FROG_ID].y += ((Entities[FROG_ID].y + msg.y >= 0) && (Entities[FROG_ID].y + msg.y < GAME_HEIGHT)) ? msg.y : 0;
                    Entities[FROG_ID].x += ((Entities[FROG_ID].x + msg.x >= 0) && (Entities[FROG_ID].x + FROG_DIM_X + msg.x <= GAME_WIDTH)) ? msg.x : 0;
                }

                // FROG has shotted
                if(msg.sig == FROG_SHOT_SIG){
                    // TO DO
                }

                break;


            // ************************** 
            // Msg from some CROCODILE
            // **************************
            case FIRST_CROCODILLE ... LAST_CROCODILLE:

                // Check if this crocodille is online or is offline
                Entities[msg.id].sig = ((Entities[msg.id].x + msg.x > GAME_WIDTH) || (Entities[msg.id].x + CROCODILE_DIM_X + msg.x < 0) ? CROCODILE_OFFLINE : CROCODILE_ONLINE);

                // Update the crocodile position only if the crocodile signal is ONLINE, else reset crocodile positin
                if(Entities[msg.id].sig == CROCODILE_ONLINE){
                    Entities[msg.id].x += msg.x;
                }
                else{
                    // TO DO
                    // reset_crocodile_position(Entities[msg.id], args);
                }
                break;

            // ************************** 
            // Msg from some TIME
            // **************************
            case TIME_ID:
            
                gameVar.time = msg.x;
                mvwprintw(score,1,5,"%d",gameVar.time);
                gameVar.time--;

            default:
                break;
        }

        // Print Game Area
        print_game_area(game);

        // Print Crocodiles
        print_crocodiles(game, Entities, gameVar.streams_speed);


        // Print the Frog
        print_frog(game, Entities[FROG_ID]);

        // Refresh the game screen
        wrefresh(game);
    }
}