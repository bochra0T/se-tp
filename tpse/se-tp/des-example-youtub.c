#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int val = 0;

void* increment(void* data) { 
    // Increment the value in a thread-safe manner
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex); // Lock the mutex before modifying the shared variable
        val++;
        pthread_mutex_unlock(&mutex); // Unlock the mutex after modifying the shared variable
    }
    return NULL;
}

int main() {
    pthread_t th_a, th_b;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create two threads that run the increment function
    pthread_create(&th_a, NULL, increment, NULL);
    pthread_create(&th_b, NULL, increment, NULL);

    // Wait for both threads to complete
    pthread_join(th_a, NULL);
    pthread_join(th_b, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the final value of the shared variable
    printf("Final value of val: %d\n", val);

    return 0;
}
