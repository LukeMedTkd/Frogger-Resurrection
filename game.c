#include <stdlib.h>
#include "game.h"
#include "struct.h"
#include "process.h"
#include "entity.h"
#include "sprites.h"

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

    // Define args array to get the correct id for the process (entity)
    int args[2];

    // Define fds array and Pipe Creation
    int fds[2];
    if(pipe(fds) == -1) {perror("Pipe call"); exit(1);}

    Character entities [4];

    //CreateProcess(pipe,listpid,void (*Frog_process)(int, int*),int* params)->Creazione processo RANA
    // Set args with FROG ID
    args[0] = FROG_ID; args[1] = FROG_ID;
    reset_frog_position(&(entities[FROG_ID]));
    create_process(fds,  entities, FROG_ID, &frog_process, args);


    //CreateProcess(pipe,listpid,void (*Time_process)(int, int*),int* params)->Creazione processo TEMPO

    /*
    for (int i = 1; i <= N_STREAM; i++){
        // randomize speed and spawn time
        for (int j = 1; j <= MAX_N_CROCODILE; i++){
            args[0] = i;
            args[1] = j;

            //CreateProcess(pipe,listpid,void (*Crocodile_process)(int, int*),int* args_process_function))->Creazione processo Coccodrillo
            //CrocodileProcess(int y, int velocità di creazione,direzione del flusso)
        }

    }*/ 
    
    /*
    FUZNIONAMENTO GENERALE DEGLI SPOSTAMENTI DELLE ENTITA:
    1. Il processo controllo, per disegnare le entità sullo schermo deve leggere le coordinate presenti nelle struct Character presenti nei nodi della lista. 
    2. Quando legge i msg dalla pipe, si occupa di aggiornare le coordinnate nelle struct Character nei nodi della lista.
    3. Quindi ad ogni inizio della manche resetta queste posizioni   
    */


   
    for(int i = 0; i < MANCHES; i++){

        // reset default position-> posizione rana (agire sul primo nodo della lista), tempo, score
        reset_frog_position(&(entities[FROG_ID]));
        //Randomizzare velocità e settare direzione dei flussi (agire sui nodidella lista)
        
        //PARENT PROCESS
        parent_process(game, fds[PIPE_READ], entities);

        
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
    

}