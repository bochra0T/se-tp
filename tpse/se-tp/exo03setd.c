#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem1, sem2; // Déclaration des sémaphores
int count = 0;    // Compteur pour suivre l'ordre d'exécution de I2

// Processus A
void* ProcessusA(void* arg) {
    while (1) {
        sem_wait(&sem1); // Attente sur sem1
        printf("Processus A : Exécution de I1\n");
        sleep(1);
        sem_post(&sem2); // Signal sur sem2
    }
    return NULL;
}

// Processus B
void* ProcessusB(void* arg) {
    while (1) {
        sem_wait(&sem2); // Attente sur sem2
        printf("Processus B : Exécution de I2\n");
        sleep(1);

        // Vérifier si I2 doit être exécuté une deuxième fois
        count++;
        if (count 1) {
            count = 0;
            sem_post(&sem1); // Signal sur sem1 (pour permettre à I1 de s'exécuter)
        } else {
            sem_post(&sem2); // Signal sur sem2 (pour permettre une autre exécution de I2)
        }
    }
    return NULL;
}

int main() {
    pthread_t threadA, threadB;

    // Initialiser les sémaphores
    sem_init(&sem1, 0, 1); // Permet à I1 de commencer
    sem_init(&sem2, 0, 0); // Bloque I2 initialement

    // Créer les threads
    pthread_create(&threadA, NULL, ProcessusA, NULL);
    pthread_create(&threadB, NULL, ProcessusB, NULL);

    // Attendre la fin des threads
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    // Détruire les sémaphores
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}
