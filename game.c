#include "game.h"
#include "struct.h"
#include "entity.h"
#include "utils.h"


void randomize_streams_speed(int *streams_speed){
    // Randomize STREAMS SPEED: FIXED for each GAME
    for (int i = 0; i < N_STREAM; i++){
        streams_speed[i] = rand_range(MAX_STREAM_SPEED, MIN_STREAM_SPEED);
    }
}

void randomize_streams_direction(int *stream_speed){
    // stream_dir takes 1 or -1 each time this fucntion is called
    int stream_dir = STREAM_DIRECTION;
    for (int i = 0; i < N_STREAM; i++){
        stream_speed[i] *= stream_dir;
        stream_dir *= INVERT_DIRECTION;
    }
}

void randomize_spawn_time(int *streams_speed, int *spawn_delays){
    // TO DO: Implementare una randomizzazione pseudo casuale che si basi anche sulla streams_speed
    int spawn_delay;
    for (int i = 0; i < N_STREAM; i++){
        spawn_delay = rand_range(MAX_SPAWN_TIME, MIN_SPAWN_TIME);
        spawn_delays[i] += spawn_delay;
    }
}

void start_game(WINDOW *score, WINDOW *game){
    //set game variables
    Game_var gameVar;
    gameVar.manche = MANCHES;
    gameVar.score = SCORE;
    gameVar.time = TIME;

    // Dynamic allocation of the characters array
    Character *Entities = malloc(N_ENTITIES * sizeof(Character));

    // Variables Statement
    int args[4] = {0}, crocodile_index;

    // Define fds array and Pipe Creation
    int fds[2];
    if(pipe(fds) == -1) {perror("Pipe call"); exit(1);}


    // Create FROG process and run his routine
    create_process(fds, Entities, FROG_ID, &frog_process, args);

    //Create TIME process
    create_process(fds, Entities, TIME_ID, &timer_process, args);

    // Set streams speed with direction on gameVar array
    randomize_streams_speed(gameVar.streams_speed);
    randomize_streams_direction(gameVar.streams_speed);
    /*----------- DEBUG randomize functions OK !!!-----------*/
    
    // Create (MAX_N_CROCODILE_PER_STREAM * N_STREAM) Crocodile Processes
    for (int i = 0; i < N_STREAM; i++){
        for (int j = 0; j < MAX_N_CROCODILE_PER_STREAM; j++){
            // Get crocodile index through i and j
            crocodile_index = FIRST_CROCODILLE + (i * MAX_N_CROCODILE_PER_STREAM) + j;

            // Set args for crocodile process  -  args[4]:  | n_stream | stream_speed_with_dir | spawn delay | entity_id
            args[0] = i;
            args[1] = gameVar.streams_speed[i];
            /*----------- DEBUG gameVar.streams_speed[i] OK !!!-----------*/
            args[2] += rand_range(MAX_SPAWN_TIME, MIN_SPAWN_TIME);
            args[3] = crocodile_index;
            
            // Reset the Crocodilles Position - Modify the characters structs
            reset_crocodile_position(&(Entities[crocodile_index]), args);

            /*----------- DEBUG reset_crocodile_position OK !!!-----------*/

            // Create CROCODILE process and run his routine
            create_process(fds, Entities, crocodile_index, &crocodile_process, args);  
        }
        args[2] = 0;
    } 
    


   /******************************************************************/
   /************************* Manche Loop ***************************/
    while(gameVar.manche > 0){
    
        // Reset default FROG position 
        reset_frog_position(&Entities[FROG_ID]);
        
        // Randomize the streams direction
        //randomize_streams_direction(gameVar.streams_speed);

        // Reset default CROCODILES position
        //for(int i = FIRST_CROCODILLE; i < LAST_CROCODILLE; i++) reset_crocodile_position(&(Entities[i]), args);

        //PARENT PROCESS
        parent_process(game,score, fds[PIPE_READ], Entities, gameVar);

        // -Legge da pipe i messaggi->controlla da quale entità sono stai mandati e li stampa a schermo
        // -Stampa Area di gioco
        // -Collisioni:
        //     Rana:
        //     -Cade nell'acqua->perde vita e manche
        //     -Rana sopra il coccodrillo
        //     -Rana nella tana già occupata->perde vita e manche
        //     -Rana sparata dal coccodrillo->perde vita e manche
        //     -Rana va dietro le tane->perde vita e manche
        //     -Rana raggiunge la tana->finisce la manche e aumenta il punteggio
        //     Proiettile:
        //     -Proiettile contro proiettile-> kill
        //     -Proiettile che esce dallo schermo-> kill
        //     Coccodrillo:
        //     -se esce dallo schermo->ricicla processi*****
          
    }
    
    // Kill Processes in the array. Parent process wait all the children
    kill_processes(Entities);
    wait_children(Entities);

    // Free the memeory of Entities array
    free(Entities);

    // Close file descriptors
    close(fds[PIPE_READ]);
    close(fds[PIPE_WRITE]);

    endwin();

    return;
}