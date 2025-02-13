#include "struct.h"
#include "game.h"
#include "entity.h"
#include "utils.h"
#include "sprites.h"
#include "collisions.h"

bool crocodiles_creation = false;
Buffer buf;

Game_var initialize_gameVar(){
    Game_var gameVar;
    gameVar.manche = MANCHES;
    gameVar.score = SCORE;
    gameVar.time = TIME;
    gameVar.lifes = LIFES;
    gameVar.outcome = NO_OUTCOME;
    gameVar.n_max_bullets = N_MAX_BULLETS;
    for (int i = 0; i < N_DENS; i++) gameVar.dens[i] = TRUE;

    return gameVar;
}

void randomize_streams_speed(int *streams_speed){
    // Randomize STREAMS SPEED: FIXED for each GAME
    for (int i = 0; i < N_STREAM; i++){
        streams_speed[i] = rand_range(MAX_STREAM_SPEED, MIN_STREAM_SPEED);
    }
}

void randomize_streams_direction(int *stream_speed){
    // stream_dir takes 1 or -1
    int stream_dir = STREAM_DIRECTION;
    for (int i = 0; i < N_STREAM; i++){
        stream_speed[i] = abs(stream_speed[i]); // invert correctly dir
        stream_speed[i] *= stream_dir;
        stream_dir *= INVERT_DIRECTION;
    }
}

void set_crocodiles_on_streams(Character *Entities, Game_var *gameVar){

    // Variables Statement
    int crocodile_index;

    // Set the streams direction to generate a new original scene
    randomize_streams_direction(gameVar->streams_speed);
    
    // Create (MAX_N_CROCODILE_PER_STREAM * N_STREAM) Crocodile Threads
    for (int i = 0; i < N_STREAM; i++){

        // variables statements
        int cumulative_delay = 0;

        for (int j = 0; j < MAX_N_CROCODILE_PER_STREAM; j++){
            // Get crocodile index through i and j
            crocodile_index = FIRST_CROCODILE + (i * MAX_N_CROCODILE_PER_STREAM) + j;

            // Allocate args for each thread
            int *args = malloc(4 * sizeof(int));

            // Set args for crocodile thread  -  args[4]:  | n_stream | stream_speed_with_dir | spawn delay | entity_id
            args[0] = i;
            args[1] = gameVar->streams_speed[i];
            cumulative_delay += rand_range(2 * (abs(args[1]) * CROCODILE_DIM_X), (abs(args[1]) * CROCODILE_DIM_X) + (abs(args[1]) * CROCODILE_DIM_X / 2));
            args[2] = cumulative_delay;
            args[3] = crocodile_index;
            
            // Reset the Crocodilles Position - Modify the characters structs
            reset_crocodile_position(&(Entities[crocodile_index]), i, gameVar);

            // Create CROCODILE thread and run his routine
            create_thread(Entities, crocodile_index, crocodile_index, crocodile_thread, args);

            // The free function is called by crocodile_thread to allow him to read all arguments
        }
    }
    crocodiles_creation = TRUE;
}

int get_nStream_based_on_id(int id){
    return (id - FIRST_CROCODILE) / MAX_N_CROCODILE_PER_STREAM;
}

void outcome(WINDOW *game, Game_var *gameVar){

    switch (gameVar->outcome){

        case WINNER_OUTCOME:
            print_won_game(game);
            break;

        case LOSER_OUTCOME:
            print_lost_game(game);
            break;
        
        case NO_OUTCOME:
        break;
    }
}

/*---------------- Main GAME function --------------------*/
void start_game(WINDOW *score, WINDOW *game){

    //set game variables
    Game_var gameVar = initialize_gameVar();

    // Dynamic allocation 
    Character *Entities = malloc(N_ENTITIES * sizeof(Character));
    Character *Bullets = malloc(N_BULLETS * sizeof(Character));

    // Intialize Entities TID
    reset_entities_tid(Entities, Bullets);

    // Reset Bullets SIGNAL
    reset_bullets_signal(Bullets);

    // Define and Initialize SHARED BUFFER
    buffer_init(&buf);

    // Create FROG thread and run his routine
    create_thread(Entities, FROG_ID, FROG_ID, frog_thread, NULL);
    
    // Create TIME thread and run his routine
    create_thread(Entities, TIME_ID, TIME_ID, timer_thread, NULL);

    // Set the streams speed, fixed for the whole game
    randomize_streams_speed(gameVar.streams_speed);
     

   /******************************************************************/
   /************************* Manche Loop ***************************/
    while(gameVar.manche > 0 && gameVar.outcome == NO_OUTCOME){

        // Reset the timer
        reset_timer(&gameVar);

        // Reset default FROG position 
        reset_frog_position(&Entities[FROG_ID]);

        // Create the crocodiles on the streams
        set_crocodiles_on_streams(Entities, &gameVar);

        // Parent Thread
        parent_thread(game, score, &buf, Entities, Bullets, &gameVar);

        // Kill all the crocodile threads to generate a new original scene
        kill_threads(Entities, FIRST_CROCODILE, LAST_CROCODILE);
        wait_threads(Entities, FIRST_CROCODILE, LAST_CROCODILE);
          
    }   

    // Print OUTCOME
    outcome(game, &gameVar);

    // Kill threads in the array.
    kill_threads(Entities, 0, N_ENTITIES);
    wait_threads(Entities, 0, N_ENTITIES);
    kill_threads(Bullets, FIRST_CROCODILE, LAST_CROCODILE);
    wait_threads(Bullets, FIRST_CROCODILE, LAST_CROCODILE);

    // Destroy the buffer
    destroy_buffer(&buf);

    // Free the allocated memeory
    free(Entities);
    free(Bullets);

    // Delete the previous GAME windows
    delwin(game);
    delwin(score);

    return;
}