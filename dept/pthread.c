#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>

#define N 100000000
unsigned int s = 0;  // Shared variable

// Mutex to protect shared variable 's'
pthread_mutex_t mutex;

void *c(void *d){
    int i;
    for (i = 0; i < N; i++) {
        pthread_mutex_lock(&mutex);  // Lock the mutex before modifying 's'
        s++;  // Critical section
        pthread_mutex_unlock(&mutex);  // Unlock the mutex after modifying 's'
    }
    return NULL;
}

int main(void) {
    pthread_t t[2];
    int r;

    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("mutex init failed");
        exit(1);
    }

    // Create the first thread
    r = pthread_create(&t[0], NULL, c, NULL); 
    if (r != 0) {
        perror("thread create:");
        exit(1);
    }

    // Create the second thread
    r = pthread_create(&t[1], NULL, c, NULL);  // Note: corrected function name 'C' to 'c'
    if (r != 0) {
        perror("thread create:");
        exit(2);
    }

    // Wait for both threads to finish
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);

    // Print the final value of 's'
    printf("%u\n", s);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

