#include <stdio.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/signal.h>
#include "struct.h"

// Define Constants
#define PID_CHILD 0
#define PIPE_READ 0
#define PIPE_WRITE 1
#define QUIT 113


// Functions Prototypes
void create_process(int *fds, Character *Entitites, int index, int id, void (*func_process)(int, int*), int* func_params);
void kill_processes(Character *Entities, int start, int end);
void wait_children(Character *Entities, int start, int end);
void write_msg(int pipe_write, Msg msg);
Msg read_msg(int pipe_read);
int create_socket();
struct sockaddr_un initialize_socket_address();
void bind_socket(int sockfd, struct sockaddr_un address);
int accept_new_connection_from_client(int sockfd);
void set_socket_nonblock(int sock_fd);
void connect_to_server(int client_fd, struct sockaddr_un server_addr);
void send_msg(int client_fd, Msg msg);
Msg receive_msg(int server_fd);