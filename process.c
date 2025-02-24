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
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket() failed");
        return -1;
    }
    return sockfd;
}

struct sockaddr_un initialize_socket_address(){
    struct sockaddr_un address;

    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);
    
    return address;
}

void bind_socket(int sockfd, struct sockaddr_un address){
   
    // Binding ...
    if(bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("bind() failed");
    } 

    // Server Socket stays on hold
    if (listen(sockfd, 5) == -1){
        perror("listen() failed");
    }
}

int accept_new_connection_from_client(int sockfd){

    int server_fd = accept(sockfd, NULL, NULL);
    
    if(server_fd == -1){
        perror("accept() failed");
        return -1;
    }
    // No error - return the server_fd
    return server_fd;
}

void set_socket_nonblock(int sock_fd){
    int flags = fcntl(sock_fd, F_GETFL, 0);
    fcntl(sock_fd, F_SETFL, flags | O_NONBLOCK);
}

void connect_to_server(int client_fd, struct sockaddr_un server_addr){
    if(connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        perror("connect() failed");
    };

    return;
}

void send_msg(int client_fd, Msg msg){
    int res = send(client_fd, &msg, sizeof(msg), 0);

    if (res < 0){
        if(errno == EAGAIN || errno == EWOULDBLOCK){
            perror("send(): socket non pronto, riprova più tardi.\n");
        } 
        else {
            
            perror("send() failed");
            return;
        }
    }
}

Msg receive_msg(int server_fd){
    Msg msg;
    recv(server_fd, &msg, sizeof(msg), 0);
    return msg;
}