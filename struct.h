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
   pid_t id;
   struct pid_node *next;

}Pid_node;

typedef struct
{
    int time;
    int manche;
    int score;    
}Game_var;



