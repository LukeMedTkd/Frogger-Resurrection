#include "process.h"
#include "struct.h"
#include "utils.h"
#include "entity.h"

void add_node(Pid_node **list,int* func_params){

        Pid_node *new = (Pid_node*)malloc(sizeof(Pid_node));
        if ((new==NULL))
        {
            puts("ERRORE:");
            exit(-1);
        }
        
        new->info.pid=getpid();//il figlio recupera il proprio pid
        new->info.id = (func_params[0]*10)+func_params[1];
        new->next = NULL;   
        
        if (*list == NULL){
            *list = new;
        }

        Pid_node *current = *list;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new;
}

void create_process(int* fd, Pid_node **list, void (*func_process)(int, int*), int* func_params) {
    pid_t pid = fork();
    if(pid < 0) {
        //signal_all(*pids, SIGKILL);
        perror("Pipe call");
    }
    if(pid == PID_CHILD) {
        close(fd[PIPE_READ]);
        add_node(&list,func_params);
        func_process(fd[PIPE_WRITE], func_params);
        _exit;
    }
}

void write_msg(int pipe_write, Msg msg){
    while(write(pipe_write, &msg, sizeof(Msg)) < 0) {
        perror("Errore in scrittura sulla pipe");
    }
}