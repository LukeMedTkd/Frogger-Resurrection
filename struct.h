#include <sys/types.h>
#include <unistd.h>
#include "game.h"

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
    int streams_speed[N_STREAM];
    int spawn_delays[N_STREAM]; 
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