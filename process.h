#include <stdio.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include "struct.h"

// Define Constants
#define PID_CHILD 0
#define PIPE_READ 0
#define PIPE_WRITE 1

//definire le altezze di ogni flusso
void add_node(Pid_node **list,int* func_params);
void create_process(int* fd, Pid_node **list, void (*func_process)(int, int*), int* func_params);
void write_msg(int pipe_write, Msg msg);
Msg read_msg(int pipe_read);
void delete_list(Pid_node **list);
