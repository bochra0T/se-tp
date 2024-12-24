#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_A, sem_B, sem_C;

void* A(void* arg) {
    printf("Processus A\n");
    sem_post(&sem_A); // signaler que A est terminé
    return NULL;
}

void* B(void* arg) {
    sem_wait(&sem_A); // attendre que A soit terminé
    printf("Processus B\n");
    sem_post(&sem_B); // signaler que B est terminé
    return NULL;
}

void* C(void* arg) {
    sem_wait(&sem_A); // attendre que A soit terminé
    printf("Processus C\n");
    sem_post(&sem_B); // signaler que C est terminé
    return NULL;
}

void* D(void* arg) {
    sem_wait(&sem_A); // attendre que B soit terminé
    printf("Processus D\n");
    sem_post(&sem_B);
    return NULL;
}

void* E(void* arg) {
    sem_wait(&sem_B); // attendre que C soit terminé
    printf("Processus E\n");
    sem_post(&sem_C);
    return NULL;
}

void* F(void* arg) {
    sem_wait(&sem_B);
    sem_wait(&sem_C); // attendre que E soit terminé
    printf("Processus F\n");
    return NULL;
}

int main() {
    pthread_t th_A, th_B, th_C, th_D, th_E, th_F;

    sem_init(&sem_A, 0, 1);
    sem_init(&sem_B, 0, 0);
    sem_init(&sem_C, 0, 0);

    pthread_create(&th_A, NULL, A, NULL);
    pthread_create(&th_B, NULL, B, NULL);
    pthread_create(&th_C, NULL, C, NULL);
    pthread_create(&th_D, NULL, D, NULL);
    pthread_create(&th_E, NULL, E, NULL);
    pthread_create(&th_F, NULL, F, NULL);

    pthread_join(th_A, NULL);
    pthread_join(th_B, NULL);
    pthread_join(th_C, NULL);
    pthread_join(th_D, NULL);
    pthread_join(th_E, NULL);
    pthread_join(th_F, NULL);

    sem_destroy(&sem_A);
    sem_destroy(&sem_B);
    sem_destroy(&sem_C);

    return 0;
}