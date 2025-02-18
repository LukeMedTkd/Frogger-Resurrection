#include <stdbool.h>
#include <sys/types.h>
#include "miniaudio.h"

#ifndef MAX_PLAYERS
#define N_STREAM 8
#define N_DENS 5
#endif

#ifndef STRUCT_H
#define STRUCT_H

typedef struct{
    char *filename;
    ma_sound sound;
}Sound;

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
   int pid;
   int id;
   int y;
   int x;
   int sig;

}Character;

#endif