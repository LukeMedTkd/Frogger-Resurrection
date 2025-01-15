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
    int time;
    int manche;
    int score;    
}Game_var;

//list for crocodiles and its own bullet id process
typedef struct
{   
   pid_t pid; 
   int id;
   int y;
   int x;
   int sig;
}Character;

typedef struct
{
    Character info;
    struct Pid_node *next;
}Pid_node;


