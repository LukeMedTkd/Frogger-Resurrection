#include <stdbool.h>
#include <sys/types.h>

#ifndef MAX_PLAYERS
#define N_STREAM 8
#define N_DENS 5
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