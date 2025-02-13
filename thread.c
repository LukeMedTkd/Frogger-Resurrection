#include "thread.h"
#include "struct.h"
#include "utils.h"
#include "entity.h"
#include "game.h"

void buffer_init(Buffer *buf){
    buf->in = buf->out = 0;
    sem_init(&(buf->sem_free_spaces), 0, BUFFER_SIZE);
    sem_init(&(buf->sem_busy_spaces), 0, 0);
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

void cleanup_mutex(void *arg) {
    pthread_mutex_unlock((pthread_mutex_t *)arg);
}

void cleanup_sem(void *arg) {
    Buffer *buf = (Buffer *)arg;
    sem_post(&buf->sem_free_spaces);
}

void write_msg(Buffer *buf, Msg msg) {

    sem_wait(&buf->sem_free_spaces);

    // Relase the semaphore resource if an interrup occurs
    pthread_cleanup_push(cleanup_sem, (void *)buf);

    // Lock the mutex - ensures the mutual exclusion
    pthread_mutex_lock(&(buf->mutex));

    // Relase the mutex resource if an interrup occurs
    pthread_cleanup_push(cleanup_mutex, (void *)&buf->mutex);

    // DEACTIVE the cancellation inside the race condition
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

    // RACE CONDITION - write in the shared buffer
    buf->buffer[buf->in] = msg;
    buf->in = (buf->in + 1) % BUFFER_SIZE;

    sem_post(&buf->sem_busy_spaces);

    // REACTIVATE the cancellation outside the race condition
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    // Remove the cleanup handler in reverse order
    pthread_cleanup_pop(0);

    // Unlock the mutex 
    pthread_mutex_unlock(&(buf->mutex));
    
    pthread_cleanup_pop(0);
}

Msg read_msg(Buffer *buf){
    sem_wait(&buf->sem_busy_spaces);         
    Msg msg = buf->buffer[buf->out];     
    buf->out = (buf->out + 1) % BUFFER_SIZE;
    sem_post(&buf->sem_free_spaces); 
    
    return msg;
}
