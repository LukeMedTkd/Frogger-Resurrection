#include <stdio.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include "struct.h"

// Define Constants
#define BUFFER_SIZE 1000

// Functions Prototypes
void buffer_init(Buffer *buf);
void create_thread(Buffer *buf,  Character *Entities, int index, int id, void *(func_thread)(void *args), int *func_params);
// void kill_processes(Character *Entities, int start, int end);
// void wait_children(Character *Entities, int start, int end);
void write_msg(Buffer *buf, Msg msg);
Msg read_msg(Buffer *buf);