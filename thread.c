#include "thread.h"
#include "struct.h"
#include "utils.h"
#include "entity.h"
#include "game.h"

void buffer_init(Buffer *buf){
    buf->in = buf->out = 0;
    sem_init(&(buf->sem_free_spaces), 0, BUFFER_SIZE); // BUFFER_SIZE spazi inizialmente liberi
    sem_init(&(buf->sem_busy_spaces), 0, 0);       // 0 elementi inizialmente presenti
    pthread_mutex_init(&(buf->mutex), NULL);
}

void destroy_buffer(Buffer *buf){
    sem_destroy(&buf->sem_busy_spaces);
    sem_destroy(&buf->sem_free_spaces);
    pthread_mutex_destroy(&buf->mutex);
}

void create_thread(Character *Entities, int index, int id, void *(func_thread), void *func_params){
        pthread_t tid;
        // If pthread_create failed
        if(pthread_create(&tid, NULL, func_thread, func_params) != 0){
            Entities[index].tid = 0;
            return;
        }

        // Set Id and tid
        Entities[index].id = id;
        Entities[index].tid = tid;
}

void kill_threads(Character *Entities, int start, int end){
    for (int i = start; i < end; i++){
        if(Entities[i].tid != 0) pthread_cancel(Entities[i].tid);
    } 
}

void wait_threads(Character *Entities, int start, int end){
    for (int i = start; i < end; i++){
        if(Entities[i].tid != 0){
            pthread_join(Entities[i].tid, NULL);
            Entities[i].tid = 0;
        }
    }   
}

void write_msg(Buffer *buf, Msg msg) {
    sem_wait(&buf->sem_free_spaces);   
    pthread_mutex_lock(&(buf->mutex)); 
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);          
    buf->buffer[buf->in] = msg;             
    buf->in = (buf->in + 1) % BUFFER_SIZE;
    sem_post(&buf->sem_busy_spaces); 
    pthread_mutex_unlock(&(buf->mutex)); 
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);   
}

Msg read_msg(Buffer *buf){
    sem_wait(&buf->sem_busy_spaces);         
    Msg msg = buf->buffer[buf->out];     
    buf->out = (buf->out + 1) % BUFFER_SIZE;
    sem_post(&buf->sem_free_spaces); 
    
    return msg;
}
