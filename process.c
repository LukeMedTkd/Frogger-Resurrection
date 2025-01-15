#include "process.h"
#include "struct.h"
#include "utils.h"

void add_node(Node **list,int stream,int y,int dir,int active){

        Node *new=(Node*)malloc(sizeof(Node));
        if ((new==NULL))
        {
            puts("ERRORE:");
            exit(-1);
        }
        new->info.id=(stream*10)+i;
        //new->info.x_entity=dir;
        //new->info.x_bullet
        new->info.dir = dir;
        new->next = NULL;
        new->info.active = 0;//non è ancora stato aseegnato a nessun processo

        if (*list == NULL){
            *list = new;
        }

        Node *current = *list;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new;
    }

void AssignementProcessToCrocodile(node **list);













































































void create_process(int* fd, Character **list, void (*func_process)(int, int*), int* func_params) {
    pid_t pid = fork();
    if(pid < 0) {
        //signal_all(*pids, SIGKILL);
        perror("Pipe call");
    }
    if(pid == PID_CHILD) {
        close(fd[PIPE_READ]);
        func_process(fd[PIPE_WRITE], func_params);
        _exit;
    }
    addNode();
}



void write_msg(int pipe_write, Msg msg) {
    while(write(pipe_write, &msg, sizeof(Msg)) < 0) {
        perror("Errore in scrittura sulla pipe");
    }
}