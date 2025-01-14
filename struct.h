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
   pid_t id;
   struct pid_node *next;

}pid_node;

typedef struct
{
    int time;
    int manche;
    int score;    
}game_var;



