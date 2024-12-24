#include <pthread.h>
#include <stdio.h>

void* A(void *data) { /* Affiche Hello world */
    printf("Hello world \n");
    return 0;
}

int main() { 
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &A, NULL);

    pthread_join(thread_id, NULL);

    return 0;
}
