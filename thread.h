#include <stdio.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include "struct.h"
#include <errno.h>

// Define Constants
#define BUFFER_SIZE 300

// Functions Prototypes
void buffer_init(Buffer *buf);
void destroy_buffer(Buffer *buf);
void create_thread(Character *Entities, int index, int id, void *(func_thread), void *func_params);
void kill_threads(Character *Entities, int start, int end);
void wait_threads(Character *Entities, int start, int end);
void write_msg(Buffer *buf, Msg msg);
Msg read_msg(Buffer *buf);