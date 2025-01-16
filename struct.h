#include <sys/types.h>
#include <unistd.h>

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
}Game_var;


typedef struct
{
   int pid;
   int id;
   int y;
   int x;
   int sig;

}Character;

typedef struct Pid_node
{
    Character info;
    struct Pid_node *next;
}Pid_node;

#endif
