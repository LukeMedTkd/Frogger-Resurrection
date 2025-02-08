#include "thread.h"
#include "struct.h"
#include "utils.h"
#include "entity.h"
#include "game.h"

void buffer_init(Buffer *buf){
    buf->in = buf->out = 0;
    sem_init(&buf->sem_busy_spaces, 0, BUFFER_SIZE); // BUFFER_SIZE spazi inizialmente liberi
    sem_init(&buf->sem_free_spaces, 0, 0);       // 0 elementi inizialmente presenti
}

void create_thread(Buffer *buf,  Character *Entities, int index, int id, void *(func_thread)(void *args), int *func_params){
        pthread_t tid;
        // If pthread_create failed
        if(pthread_create(&tid, NULL, func_thread, func_params) > 0){
            // KILL, WAIT and destroy SEMAPHORE
            return;
        }

        // Set Id and tid
        Entities[index].id = id;
        Entities[index].tid = tid;
}

// void kill_processes(Character *Entities, int start, int end){
//     for (int i = start; i < end; i++){
//         if(Entities[i].pid != 0) kill(Entities[i].pid, SIGKILL);
//     }   
// }

// void wait_children(Character *Entities, int start, int end){
//     for(int i = start; i < end; i++){
//         if(Entities[i].pid != 0) waitpid(Entities[i].pid, NULL, WNOHANG);
//     }
// }

void write_msg(Buffer *buf, Msg msg){
    sem_wait(&(buf->sem_busy_spaces));              
    buf->buffer[buf->in] = msg;         
    buf->in = (buf->in + 1) % BUFFER_SIZE; 
    sem_post(&(buf->sem_free_spaces));         
}   

Msg read_msg(Buffer *buf){
    sem_wait(&(buf->sem_free_spaces));            
    Msg msg = buf->buffer[buf->out];       
    buf->out = (buf->out + 1) % BUFFER_SIZE; 
    sem_post(&(buf->sem_busy_spaces));
    return msg;
}