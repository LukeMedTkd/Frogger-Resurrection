#include <sys/types.h>
#include <unistd.h>

typedef struct
{
    int id;
    int y;
    int x;
    int sig;
}msg;

typedef struct
{
   pid_t* list;
   int lenght;

}pid_node;

typedef struct
{
    int time;
    int manche;
    int score;    
}game_var;

//list for crocodiles and its own bullet id process
typedef struct
{
   int id;
   int y;
   int x_entity;
   int x_bullet;
   int dir;
   int active;

}character;

typedef struct
{
    character info;
    struct node *next;
}node;


