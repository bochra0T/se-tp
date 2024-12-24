#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_S1, sem_S2;

int A = 5, B = 3;
int S1, S2, S3;

void* P1(void* arg) {
    S1 = A + B;
    printf("P1 : S1 = %d\n", S1);
    sem_post(&sem_S1); // signaler que S1 est calculé
    return NULL;
}

void* P2(void* arg) {
    sem_wait(&sem_S1); // attendre que S1 soit calculé
    S2 = 2 * S1 + 4;
    printf("P2 : S2 = %d\n", S2);
    sem_post(&sem_S2); // signaler que S2 est calculé
    return NULL;
}

void* P3(void* arg) {
   // attendre que S1 soit calculé
    sem_wait(&sem_S2); // attendre que S2 soit calculé
    S3 = S1 + S2;
    printf("P3 : S3 = %d\n", S3);
    return NULL;
}

int main() {
    pthread_t th_P1, th_P2, th_P3;

    sem_init(&sem_S1, 0, 0);
    sem_init(&sem_S2, 0, 0);

    pthread_create(&th_P1, NULL, P1, NULL);
    pthread_create(&th_P2, NULL, P2, NULL);
    pthread_create(&th_P3, NULL, P3, NULL);

    pthread_join(th_P1, NULL);
    pthread_join(th_P2, NULL);
    pthread_join(th_P3, NULL);

    sem_destroy(&sem_S1);
    sem_destroy(&sem_S2);

    return 0;
}