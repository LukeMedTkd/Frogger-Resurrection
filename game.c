#include "game.h"
#include "struct.h"
#include "entity.h"
#include "utils.h"
#include "sprites.h"
#include "collisions.h"
#include "sound.h"

bool crocodiles_creation = false;
extern Sound sounds[N_SOUND]; 

Game_var initialize_gameVar(){
    Game_var gameVar;
    gameVar.manche = MANCHES;
    gameVar.score = SCORE;
    gameVar.time = TIME;
    gameVar.lifes = LIFES;
    gameVar.outcome = NO_OUTCOME;
    gameVar.n_max_bullets = N_MAX_BULLETS;
    for (int i = 0; i < N_DENS; i++){ gameVar.dens[i] = TRUE; }

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

void set_crocodiles_on_streams(Character *Entities, int *fds, Game_var *gameVar){
        // Variables Statement
        int args[4] = {0}, crocodile_index;

        // Set the streams direction to generate a new original scene
        randomize_streams_direction(gameVar->streams_speed);
        
        // Create (MAX_N_CROCODILE_PER_STREAM * N_STREAM) Crocodile Processes
        for (int i = 0; i < N_STREAM; i++){
            for (int j = 0; j < MAX_N_CROCODILE_PER_STREAM; j++){
                // Get crocodile index through i and j
                crocodile_index = FIRST_CROCODILE + (i * MAX_N_CROCODILE_PER_STREAM) + j;
                // Set args for crocodile process  -  args[4]:  | n_stream | stream_speed_with_dir | spawn delay | entity_id
                args[0] = i;
                args[1] = gameVar->streams_speed[i];
                args[2] += rand_range(2 * (abs(args[1]) * CROCODILE_DIM_X), (abs(args[1]) * CROCODILE_DIM_X) + (abs(args[1]) * CROCODILE_DIM_X/2));
                args[3] = crocodile_index;
                
                // Reset the Crocodilles Position - Modify the characters structs
                reset_crocodile_position(&(Entities[crocodile_index]), i, gameVar);

                // Create CROCODILE process and run his routine
                create_process(fds, Entities, crocodile_index, crocodile_index, &crocodile_process, args);  
            }
            args[2] = 0;
        }
        crocodiles_creation = TRUE;
}

int get_nStream_based_on_id(int id){
    return (id - FIRST_CROCODILE) / MAX_N_CROCODILE_PER_STREAM;
}

void outcome(WINDOW *game, Game_var *gameVar){

    switch (gameVar->outcome){

        case WINNER_OUTCOME:
            play_sound(&sounds[WON].sound);
            print_won_game(game);
            break;

        case LOSER_OUTCOME:
            play_sound(&sounds[LOST].sound);
            print_lost_game(game);
            stop_sound(&sounds[LOST].sound);
            break;
        
        case NO_OUTCOME:
        break;
    }
}


/*---------------- Main GAME function --------------------*/
void start_game(WINDOW *score, WINDOW *game){

    // Set game variables
    Game_var gameVar = initialize_gameVar();

    // Dynamic allocation 
    Character *Entities = malloc(N_ENTITIES * sizeof(Character));
    Character *Bullets = malloc(N_BULLETS * sizeof(Character));

    // Reset Bullets SIGNAL
    reset_bullets_signal(Bullets);

    // Define fds array and Pipe Creation
    int fds[2];
    if(pipe(fds) == -1) {perror("Pipe call"); exit(1);}

    // Create Server and Client Socket
    int server_fd = create_socket();
    int client_fd = create_socket();
    set_socket_nonblock(client_fd);

    // Initialize the socket address
    unlink(SOCKET_PATH);
    struct sockaddr_un address = initialize_socket_address();
    
    // Server Socket Bind
    bind_socket(server_fd, address);
    
    // Create FROG process and run his routine
    int args[2]; args[0] = client_fd;
    create_process(fds, Entities, FROG_ID, FROG_ID, &frog_process, args);

    // Accept new connection from client
    int new_conn_fd = accept_new_connection_from_client(server_fd);
    set_socket_nonblock(new_conn_fd);

    // Create TIME process and run his routine
    create_process(fds, Entities, TIME_ID, TIME_ID, &timer_process, NULL);

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
        set_crocodiles_on_streams(Entities, fds, &gameVar);

        // Play the soundtrack manche
        play_sound(&sounds[MANCHE].sound);

        // Parent Process
        parent_process(game, score, fds, new_conn_fd, Entities, Bullets, &gameVar);

        // Stop the soundtrack manche
        stop_sound(&sounds[MANCHE].sound);

        // Kill all the crocodile processes and their bullets to generate a new original scene
        kill_processes(Entities, FIRST_CROCODILE, LAST_CROCODILE);
        wait_children(Entities, FIRST_CROCODILE, LAST_CROCODILE);
          
    }   

    // Print OUTCOME
    outcome(game, &gameVar);

    // Kill Processes in the array.
    kill_processes(Entities, 0, N_ENTITIES);
    wait_children(Entities, 0, N_ENTITIES);
    kill_processes(Bullets, 0, N_BULLETS);
    wait_children(Bullets, 0, N_BULLETS);


    // Free the allocated memory
    free(Entities);
    free(Bullets);

    // Close file descriptors
    close(fds[PIPE_READ]);
    close(fds[PIPE_WRITE]);

    // Close the sockets
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH);

    // Delete the previous GAME windows
    delwin(game);
    delwin(score);

    return;
}