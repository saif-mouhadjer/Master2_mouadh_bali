#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include "shared.h"

void producer() {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100;

        if (sem_trywait(empty) != 0) {
            printf("Producer => buffer is full\n\n");
            sem_wait(empty);
        }

        pthread_mutex_lock(mutex);

        printf("Producer : \n ");


        buffer[*count] = item;
        
        (*count)++;

        printf("Buffer  => ");
        print_buffer("after");

        pthread_mutex_unlock(mutex);
        sem_post(full);

        usleep(200000);
    }
}

void consumer() {
    int item;
    for (int i = 0; i < 10; i++) {
        if (sem_trywait(full) != 0) {
            printf("Consumer => buffer is empty\n\n");
            sem_wait(full);
        }

        pthread_mutex_lock(mutex);
        
        printf("Consumer : \n");


        item = buffer[0];
        

        for (int j = 0; j < *count - 1; j++) {
            buffer[j] = buffer[j + 1];
        }
        buffer[*count - 1] = -1;
        (*count)--;

        printf("Buffer => ");
        print_buffer("after");

        pthread_mutex_unlock(mutex);
        sem_post(empty);

        sleep(1);
    }
}

int main() {
    setup_shared_memory();

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // العملية الفرعية: المستهلك
        consumer();
    } else {
        // العملية الأصلية: المنتج
        producer();
        wait(NULL); // انتظر انتهاء المستهلك
    }

    cleanup_shared_memory();
    return 0;
}
