#include <stdio.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <errno.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include "struct.h"


// Functions Prototypes
void buffer_init(Buffer *buf);
void destroy_buffer(Buffer *buf);
void create_thread(Character *Entities, int index, int id, void *(func_thread), void *func_params);
void kill_threads(Character *Entities, int start, int end);
void wait_threads(Character *Entities, int start, int end);
void write_msg(Buffer *buf, Msg msg);
Msg read_msg(Buffer *buf);
int create_socket();
struct sockaddr_un initialize_socket_address();
void bind_socket(int sockfd, struct sockaddr_un address);
int accept_new_connection_from_client(int sockfd);
void set_socket_nonblock(int sock_fd);
void connect_to_server(int client_fd, struct sockaddr_un server_addr);
void send_msg(int client_fd, Msg msg);
Msg receive_msg(int server_fd);