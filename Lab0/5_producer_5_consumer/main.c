// main.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>
#include "shared.h"

void *producer(void *arg) {
    int item;
    int id = *((int *)arg);  // Get producer id
    for (int i = 0; i < 10; i++) {  // Produce 10 items for this example
        item = rand() % 100;  // Produce an item

        // Check if the buffer is full
        if (sem_trywait(empty) != 0) {
            printf("\nProducer %d => \n", id);
            printf("\t buffer is full...\n");
            sem_wait(empty);  // Wait for an empty slot
        }

        pthread_mutex_lock(mutex);  // Lock the buffer


        // Add item to the buffer
        buffer[*count] = item;
        printf("Producer %d \n", id);
        (*count)++;

        printf("Buffer => ");
        print_buffer("after");  // Print buffer after adding item

        pthread_mutex_unlock(mutex);  // Unlock the buffer
        sem_post(full);  // Signal that there’s a new full slot

        usleep(200000);  // Simulate time taken to produce
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    int id = *((int *)arg);  // Get consumer id
    for (int i = 0; i < 10; i++) {  // Consume 10 items for this example
        // Check if the buffer is empty
        if (sem_trywait(full) != 0) {
            printf("Consumer %d => \n", id);
            printf("\t buffer is empty...\n");
            sem_wait(full);  // Wait for a full slot
        }

        pthread_mutex_lock(mutex);  // Lock the buffer


        // Remove item from the buffer
        item = buffer[0];
        printf("\nConsumer %d => \n", id);

        // Shift all items in the buffer to the left
        for (int j = 0; j < *count - 1; j++) {
            buffer[j] = buffer[j + 1];
        }
        buffer[*count - 1] = -1;  // Mark the last position as empty
        (*count)--;

        printf("Buffer => ");
        print_buffer("after");  // Print buffer after removing item

        pthread_mutex_unlock(mutex);  // Unlock the buffer
        sem_post(empty);  // Signal that there’s an empty slot

        sleep(1);  // Simulate time taken to consume
    }
    return NULL;
}

int main() {
    setup_shared_memory();

    int num_producers = 5;
    int num_consumers = 5;
    pthread_t producers[num_producers];
    pthread_t consumers[num_consumers];
    int producer_ids[num_producers];
    int consumer_ids[num_consumers];

    // Create producer threads
    for (int i = 0; i < num_producers; i++) {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < num_consumers; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    // Wait for all producers to finish
    for (int i = 0; i < num_producers; i++) {
        pthread_join(producers[i], NULL);
    }

    // Wait for all consumers to finish
    for (int i = 0; i < num_consumers; i++) {
        pthread_join(consumers[i], NULL);
    }

    cleanup_shared_memory();
    return 0;
}
