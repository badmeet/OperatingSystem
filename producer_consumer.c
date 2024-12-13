#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

sem_t *empty;
sem_t *full;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void *producer(void *arg) {
    int i;
    for (i = 0; i < 10; i++) {
        sem_wait(empty);
        buffer[in] = i;
        printf("Produced %d\n", i);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(full);
    }
    return NULL;
}

void *consumer(void *arg) {
    int i, item;
    for (i = 0; i < 10; i++) {
        sem_wait(full);
        item = buffer[out];
        printf("Consumed %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(empty);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    
    // Initialize semaphores
    empty = sem_open("/empty", O_CREAT, 0644, BUFFER_SIZE); // -->  FOR LINUX, use sem_init(&empty, 0, BUFFER_SIZE)
    full = sem_open("/full", O_CREAT, 0644, 0); // --> FOR LINUX, use sem_init(&full, 0, 0)
    
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    
    sem_close(empty);
    sem_close(full);
    sem_unlink("/empty");
    sem_unlink("/full");
    
    return 0;
}