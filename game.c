#include "game.h"
#include "struct.h"

/*
1. creazione iniziale frog -> inserimento in una lista con FROG_ID perchè? va ucciso il processo
2. creazione iniziale dei crocodilles
for i=0; i < n_manches, i++
    play_manche();
        creazione processi 



 */
void start_game(){
    //set game variables
    Game_var gameVar;
    gameVar.manche = MANCHES;
    gameVar.score = SCORE;
    gameVar.time = TIME;

    // define args_process_function
    int *args_process_function[2];

    //CreateProcess(pipe,listpid,void (*Frog_process)(int, int*),int* params)->Creazione processo RANA
    //CreateProcess(pipe,listpid,void (*Time_process)(int, int*),int* params)->Creazione processo TEMPO
    for (int i = 1; i <= N_STREAM; i++){
        // randomize speed and spaq time
        for (int j = 1; j <= MAX_N_CROCODILE; i++){
            args_process_function[0] = i;
            args_process_function[1] = j;
            //CreateProcess(pipe,listpid,void (*Crocodile_process)(int, int*),int* params))->Creazione processo Coccodrillo
            //CrocodileProcess(int y, int velocità di creazione,direzione del flusso)
        }
        
    }
    
    for (int i = 0; i < MANCHES; i++){
        //reset default position-> posizione rana, tempo, score
        //Randomizzare velocità e settare direzione dei flussi
        
        /*ProcessoControllo
        -Legge da pipe i messaggi->controlla da quale entità sono stai mandati e li stampa a schermo
        -Stampa Area di gioco
        -Collisioni:
            Rana:
            -Cade nell'acqua->perde vita e manche
            -Rana sopra il coccodrillo
            -Rana nella tana già occupata->perde vita e manche
            -Rana sparata dal coccodrillo->perde vita e manche
            -Rana va dietro le tane->perde vita e manche
            -Rana raggiunge la tana->finisce la manche e aumenta il punteggio
            Proiettile:
            -Proiettile contro proiettile-> kill
            -Proiettile che esce dallo schermo-> kill
            Coccodrillo:
            -se esce dallo schermo->ricicla processi*****
        */
        
    }
    

}