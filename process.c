#include "process.h"
#include "struct.h"
#include "utils.h"
#include "entity.h"
#include "game.h"

void create_process(int *fds,  Character *Entities, int index, int id, void (*func_process)(int, int*), int *func_params){
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
        Entities[index].id = id;
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

int create_socket(){
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("socket");
        return -1;
    }

    //Set new flags to socket_fd to make it NON BLOCKING
    if (fcntl(socket_fd, F_SETFL, O_NONBLOCK) == -1) {
        perror("fcntl (F_SETFL)");
        close(socket_fd);
        return -1;
    }

    return socket_fd;
}

void bind_socket(int server_fd){
    struct sockaddr_in server_addr;

    // Set sockaddr_un fields;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY returns localhost
    server_addr.sin_port = htons(8000); // local port

    // Binding ...
    if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("bind() failed");
    } 

    // Server Socket stays on hold
    if (listen(server_fd, 1) == -1){
        perror("listen() failed");
    }
}

int accept_new_connection_from_client(int server_fd){
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(server_fd, NULL, NULL);
    
    if(client_fd == -1){
        perror("accept() failed");
    }

    // No error - return the client_fd
    return client_fd;
}

void connect_to_server(struct sockaddr *server_addr, int client_fd){

     // The client try to establish a new connection with server - the client_fd is set to NONBLOCK
    if(connect(client_fd, (struct sockaddr *)server_addr, sizeof(*server_addr))){
        perror("connect() failed");
    }
}

void send_msg(int client_fd, Msg msg){
    if (send(client_fd, &msg, sizeof(msg), 0) < 0){
        perror("Send Error");
        close(client_fd);
        return;
    }
}

Msg receive_msg(int client_fd){
    Msg msg;
    if(recv(client_fd, &msg, sizeof(Msg), 0) < 0){
        perror("Receive Error");
        return;
    }
    return msg;
}