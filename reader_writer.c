#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

// Shared variables
int shared_resource = 0;
int reader_count = 0;

// Semaphores and mutex
sem_t resource_access;    // Controls access to shared resource
sem_t reader_count_mutex; // Controls access to reader_count
sem_t write_block;        // Blocks writers when readers are reading

void* reader(void* arg) {
    int reader_id = *((int*)arg);
    
    while (1) {
        // Entry section
        sem_wait(&reader_count_mutex);
        reader_count++;
        if (reader_count == 1) {
            // First reader blocks writers
            sem_wait(&write_block);
        }
        sem_post(&reader_count_mutex);
        
        // Critical section (reading)
        printf("Reader %d: reading value = %d\n", reader_id, shared_resource);
        sleep(1); // Simulating reading time
        
        // Exit section
        sem_wait(&reader_count_mutex);
        reader_count--;
        if (reader_count == 0) {
            // Last reader allows writers
            sem_post(&write_block);
        }
        sem_post(&reader_count_mutex);
        
        sleep(rand() % 3); // Random delay before next read
    }
    return NULL;
}

void* writer(void* arg) {
    int writer_id = *((int*)arg);
    
    while (1) {
        // Entry section
        sem_wait(&write_block);
        sem_wait(&resource_access);
        
        // Critical section (writing)
        shared_resource++;
        printf("Writer %d: wrote value = %d\n", writer_id, shared_resource);
        sleep(1); // Simulating writing time
        
        // Exit section
        sem_post(&resource_access);
        sem_post(&write_block);
        
        sleep(rand() % 3); // Random delay before next write
    }
    return NULL;
}

int main() {
    // Initialize semaphores
    //sem_init(&resource_access, 0, 1); // --> for linux , use sem_init
    //sem_init(&reader_count_mutex, 0, 1); // --> for linux , use sem_init
    //sem_init(&write_block, 0, 1); // --> for linux , use sem_init
    
    sem_open(&resource_access,0,1); // --> for mac use sem_open
    sem_open(&reader_count_mutex,0,1);
    sem_open(&write_block,0,1);

    // Create reader and writer threads
    pthread_t readers[3], writers[2];
    int reader_ids[3] = {1, 2, 3};
    int writer_ids[2] = {1, 2};
    
    // Create reader threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    
    // Create writer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    
    // Join threads (in practice, use proper termination)
    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }
    
    // Cleanup
    sem_destroy(&resource_access);
    sem_destroy(&reader_count_mutex);
    sem_destroy(&write_block);
    
    return 0;
}