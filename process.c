#include "process.h"
#include "struct.h"
#include "utils.h"
#include "entity.h"
#include "game.h"

void create_process(int *fds,  Character *Entities, int index,  void (*func_process)(int, int*), int *func_params){
    pid_t pid = fork();
    if(pid < 0) {
        kill_processes(Entities, 0, N_ENTITIES);
        perror("Pipe call");
        exit(0);
    }
    else if(pid == PID_CHILD) {
        close(fds[PIPE_READ]);
        func_process(fds[PIPE_WRITE], func_params);
    }
    else{
        // Set Id and Pid
        Entities[index].id = index;
        Entities[index].pid = pid;
    }
}

void kill_processes(Character *Entities, int start, int end){
    for (int i = start; i < end; i++){
        if(Entities[i].pid != 0) kill(Entities[i].pid, SIGKILL);
    }   
}

void wait_children(Character *Entities, int start, int end){
    for(int i = start; i < end; i++){
        if(Entities[i].pid != 0) waitpid(Entities[i].pid, NULL, WNOHANG);
    }
}

void write_msg(int pipe_write, Msg msg){
    while(write(pipe_write, &msg, sizeof(Msg)) < 0){
        perror("Errore in scrittura sulla pipe");
    }
}

Msg read_msg(int pipe_read){
    Msg msg;
    while(read(pipe_read, &msg, sizeof(Msg)) < 0) {
        perror("Errore in lettura sulla pipe");
    }
    return msg;
}