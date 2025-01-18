#include "process.h"
#include "struct.h"
#include "utils.h"
#include "entity.h"

void create_process(int *fds,  Pid_node **Entities, int index,  void (*func_process)(int, int*), int *func_params){
    pid_t pid = fork();
    if(pid < 0) {
        //signal_all(*pids, SIGKILL);
        perror("Pipe call");
        exit(0);
    }
    if(pid == PID_CHILD) {
        close(fds[PIPE_READ]);
        func_process(fds[PIPE_WRITE], func_params);
    }
    add_node(Entities,func_params, pid);
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

void add_node(Pid_node **Entities, int* func_params, pid_t child_pid){

        Pid_node *new = (Pid_node *)malloc(sizeof(Pid_node));
        if ((new==NULL))
        {
            puts("ERRORE:");
            exit(1);
        }
        
        new->info.pid = child_pid;
        new->info.id = (func_params[0]*10)+func_params[1];
        new->next = NULL;   
        
        if (*Entities == NULL){
            *Entities = new;
            return;
        }

        else{
            Pid_node *current = *Entities;
            while (current != NULL)
            {
                current = current->next;
            }
            current->next = new;
        }
}

void delete_list(Pid_node **Entities){ 

    Pid_node *tmp;
    while (*Entities != NULL){
        tmp = *Entities;
        *Entities = (*Entities)->next;
        free(tmp);//deallocate memory
    }
}
