#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int value_globale = 1;
sem_t s1,s2;
void* increment(void* arg) {
    for (int i = 0; i < 10000000; i++) {
        value_globale++;
    }
     sem_post(&s1); 
    return NULL;
}

void* decrement(void* arg) {
    sem_wait(&s1);
    for (int i = 0; i < 10000000; i++) {
        value_globale--;
    }
      sem_post(&s1);
    return NULL;
}
int main() {
    pthread_t th,th2;
    sem_init(&s1,0,0);
    sem_init(&s2,0,0);
    pthread_create(&th, NULL, increment, NULL);
    pthread_create(&th2, NULL, decrement, NULL);

    pthread_join(th, NULL);
    pthread_join(th2, NULL);
    printf("Valeur value_globale : %d\n", value_globale);

    return 0;
}
