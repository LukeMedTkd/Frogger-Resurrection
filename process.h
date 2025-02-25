#include <sys/wait.h>
#include <sys/signal.h>
#include "struct.h"

// Define Constants
#define PID_CHILD 0
#define PIPE_READ 0
#define PIPE_WRITE 1
#define QUIT 113

// Functions Prototypes
void create_process(int *fds, Character *Entitites, int index, int id, void (*func_process)(int, int*), int* func_params);
void kill_processes(Character *Entities, int start, int end);
void wait_children(Character *Entities, int start, int end);
void write_msg(int pipe_write, Msg msg);
Msg read_msg(int pipe_read);