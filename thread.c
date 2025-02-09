#include "thread.h"
#include "struct.h"
#include "utils.h"
#include "entity.h"
#include "game.h"

int read_index = 0;
int write_index = 0;

void buffer_init(Buffer *buf){
    buf->in = buf->out = 0;
    sem_init(&(buf->sem_busy_spaces), 0, BUFFER_SIZE); // BUFFER_SIZE spazi inizialmente liberi
    sem_init(&(buf->sem_free_spaces), 0, 0);       // 0 elementi inizialmente presenti
    pthread_mutex_init(&(buf->mutex), NULL);
    write_index = 0;
}

void destroy_buffer(Buffer *buf){
    sem_destroy(&buf->sem_busy_spaces);
    sem_destroy(&buf->sem_free_spaces);
    pthread_mutex_destroy(&buf->mutex);
}

void create_thread(Buffer *buf,  Character *Entities, int index, int id, void *(func_thread)(void *args), int *func_params){
        pthread_t tid;
        // If pthread_create failed
        if(pthread_create(&tid, NULL, func_thread, func_params) != 0){
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


void cleanup_release_sem(void *arg){
    sem_t *sem = (sem_t *) arg;
    sem_post(sem);
}

void write_msg(Buffer *buf, Msg msg) {

    // The sem_wait is a cancellation point
    if (sem_wait(&(buf->sem_busy_spaces)) == -1){
        perror("sem_wait");
        exit(-1);
    }

    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    if(pthread_mutex_lock(&buf->mutex) != 0) { // Handle mutex lock error
        perror("lock error");
        exit(-1);
    }
    
    // Race condition: writing to the buffer
    buf->buffer[write_index] = msg;
    write_index = (write_index + 1) % BUFFER_SIZE;
    

    if(pthread_mutex_unlock(&buf->mutex) != 0) { // Handle mutex lock error
        perror("lock error");
        exit(-1);
    }
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    // Release the sem
    sem_post(&(buf->sem_free_spaces));
    
}

Msg read_msg(Buffer *buf){
    Msg msg;

    while(sem_wait(&buf->sem_free_spaces) != 0) {
        if(errno != EINTR) perror("sem_wait");
    }
    
     // Race condition: reading from the buffer
    msg = buf->buffer[read_index];
    read_index = (read_index + 1) % BUFFER_SIZE;
    
    // Release the sem
    while(sem_post(&buf->sem_busy_spaces) != 0) {
        if(errno != EINTR) perror("post_wait");
    }
    
    return msg;
}

