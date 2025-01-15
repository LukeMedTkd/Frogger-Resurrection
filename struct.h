#include <sys/types.h>
#include <unistd.h>

typedef struct
{
    int id;
    int y;
    int x;
    int sig;
}Msg;

typedef struct
{
   pid_t* list;
   int lenght;

}Pid_node;

typedef struct
{
    int time;
    int manche;
    int score;    
}Game_var;

//list for crocodiles and its own bullet id process
typedef struct
{
   int id;
   int y;
   int x_entity;
   int x_bullet;
   int dir;
   int active;

}Character;

typedef struct
{
    Character info;
    struct node *next;
}Node;


