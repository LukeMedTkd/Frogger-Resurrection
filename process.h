#include <stdio.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include "struct.h"

// Define Constants
#define PID_CHILD 0
#define PIPE_READ 0
#define PIPE_WRITE 1

//definire le altezze di ogni flusso
void create_process(int *fds, Pid_node **Entitites, int index, void (*func_process)(int, int*), int* func_params);
void write_msg(int pipe_write, Msg msg);
Msg read_msg(int pipe_read);

void add_node(Pid_node **Entities,int* func_params, pid_t child_pid);
void delete_list(Pid_node **Entities);
