#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>

#ifndef MAX_PLAYERS
#define N_STREAM 8
#define N_DENS 5
#define BUFFER_SIZE 300
#endif

#ifndef STRUCT_H
#define STRUCT_H

typedef struct
{
    int id;
    int y;
    int x;
    int sig;
}Msg;

typedef struct
{
    int time;
    int manche;
    int score;   
    int lifes;
    int outcome;
    int n_max_bullets;
    int streams_speed[N_STREAM];
    int spawn_delays[N_STREAM]; 
    bool dens[N_DENS];
}Game_var;


typedef struct
{
   int tid;
   int id;
   int y;
   int x;
   int sig;

}Character;

typedef struct {
    Msg buffer[BUFFER_SIZE];
    int in, out;
    sem_t sem_busy_spaces;    // Semaforo per gli spazi liberi
    sem_t sem_free_spaces; // Semaforo per gli elementi disponibili
    pthread_mutex_t mutex;
}Buffer;

#endif