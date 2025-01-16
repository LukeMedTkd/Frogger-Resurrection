#include "entity.h"
#include "struct.h"
/*
1.frogProcess-> (pipe, *params)
2.Crocodile process-> (pipe, *params)
3.Bullet process-> (pipe, *params)
*/

void frog_process(int pipe_write, int* params){

    // Init some variables
    int move, direction = 1;
    bool msg_to_send = FALSE; // avoid writing no movements

    // Declare msg and attr
    Msg msg;
    msg.id = FROG_ID;
    msg.sig = FROG_POSITION_SIG;

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
                msg.x = FROG_DIM_X * direction;
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

void reset_frog_position(Pid_node **list){
    (*list)->info.x = FROG_INIT_X;
    (*list)->info.y = FROG_INIT_Y;
}

void parent_process(int pipe_read, Pid_node **list){
    bool manche_ended = FALSE; // Flag
    Msg msg; // Define msg to store pipe message

    // Manche Loop
    while(!manche_ended){

        // Read msg from the pipe
        msg = read_msg(pipe_read);

        switch (msg.id){

        // Msg from FROG
        case FROG_ID:

            // FROG has moved - Update POSITION
            if(msg.sig == FROG_POSITION_SIG){
                (*list)->info.x += msg.x;
                (*list)->info.y += msg.y;
            }

            // FROG has shotted
            if(msg.sig == FROG_POSITION_SIG){
                // TO DO
            }

            break;
        
        default:
            break;
        }
    }

}