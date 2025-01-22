#include "game.h"
#include "struct.h"
#include "entity.h"
#include "utils.h"

/*
1. creazione iniziale frog -> inserimento in una lista con FROG_ID perchè? va ucciso il processo
2. creazione iniziale dei crocodilles
for i=0; i < n_manches, i++
    play_manche();
        creazione processi 
 */


void start_game(WINDOW *score, WINDOW *game){
    //set game variables
    Game_var gameVar;
    gameVar.manche = MANCHES;
    gameVar.score = SCORE;
    gameVar.time = TIME;

    // Variables Declaration
    int args[3] = {0}, stream_speed, spawn_delay = 0, stream_dir, crocodile_index = 2;

    // Define fds array and Pipe Creation
    int fds[2];
    if(pipe(fds) == -1) {perror("Pipe call"); exit(1);}

    // Define CArray of Characters
    Character Entities[N_ENTITIES];

    // Create FROG process
    create_process(fds, Entities, FROG_ID, &frog_process, args);


    //CreateProcess(pipe,listpid,void (*Time_process)(int, int*),int* params)->Creazione processo TEMPO
    stream_dir = STREAM_DIRECTION;
    for (int i = 0; i < N_STREAM; i++){
        // Randomize STREAM SPEED: FIXED for each GAME
        stream_speed = rand_range(MAX_STREAM_SPEED, MIN_STREAM_SPEED);
        for (int j = 0; j < MAX_N_CROCODILE_PER_STREAM; j++){
            // Set args for crocodile process  -  args[3]:  | n_stream | stream_speed_with_dir | spawn delay |
            args[0] = i;
            args[1] = stream_speed * stream_dir;
            args[2] += spawn_delay;
            spawn_delay = rand_range(MAX_SPAWN_TIME, MIN_SPAWN_TIME);

            // Reset the Crocodilles Position - Modify the characters structs
            reset_crocodile_position(&(Entities[crocodile_index]), args);
        
            // Create CROCODILE process
            create_process(fds, Entities, crocodile_index, &crocodile_process, args);
            crocodile_index++;
        }

        spawn_delay = args[2] = 0;
        stream_dir *= INVERT_DIRECTION;
    } 
    
    /*
    FUNZIONAMENTO GENERALE DEGLI SPOSTAMENTI DELLE ENTITA:
    1. Il processo controllo, per disegnare le entità sullo schermo deve leggere le coordinate presenti nelle struct Character presenti nell'array 
    2. Quando legge i msg dalla pipe, si occupa di aggiornare le coordinnate nelle struct Character dell' array.
    3. Quindi ad ogni inizio della manche resetta queste posizioni   
    */


   
    while(gameVar.manche > 0){
    
        // reset default position-> posizione rana (agire sul primo nodo della lista), tempo, score
        reset_frog_position(&Entities[FROG_ID]);
        //Randomizzare velocità e settare direzione dei flussi (agire sui nodidella lista)

        //PARENT PROCESS
        parent_process(game, fds[PIPE_READ], Entities, gameVar);

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
    
    // Kill Processes in the list. Parent process wait all the children
    kill_processes(Entities);
    wait_children(Entities);

    // Close file descriptors
    close(fds[PIPE_READ]);
    close(fds[PIPE_WRITE]);

    endwin();

    return;
}