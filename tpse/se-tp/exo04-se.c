#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define NB_THREADS 8  // Nombre total de threads

sem_t semVide;  // Sémaphore pour gérer le tampon vide
sem_t semPlein; // Sémaphore pour gérer le tampon plein

pthread_mutex_t mutexTampon; // Mutex pour protéger l'accès au tampon

int tampon[10];  // Taille du tampon
int nbMessages = 0; // Compteur du nombre de messages dans le tampon

// Fonction du producteur
void* producteur(void* args) {
    while (1) {
        // Produire un message (valeur aléatoire)
        int message = rand() % 100;
        sleep(1);

        // Ajouter le message dans le tampon
        sem_wait(&semVide);  // Attendre que de l'espace soit disponible dans le tampon
        pthread_mutex_lock(&mutexTampon);  // Verrouiller l'accès au tampon
        tampon[nbMessages] = message;  // Placer le message dans le tampon
        nbMessages++;
        pthread_mutex_unlock(&mutexTampon);  // Déverrouiller l'accès au tampon
        sem_post(&semPlein);  // Signaler qu'il y a un nouveau message dans le tampon
    }
}

// Fonction du consommateur
void* consommateur(void* args) {
    while (1) {
        int message;

        // Retirer un message du tampon
        sem_wait(&semPlein);  // Attendre que le tampon ne soit pas vide
        pthread_mutex_lock(&mutexTampon);  // Verrouiller l'accès au tampon
        message = tampon[nbMessages - 1];  // Retirer le dernier message du tampon
        nbMessages--;
        pthread_mutex_unlock(&mutexTampon);  // Déverrouiller l'accès au tampon
        sem_post(&semVide);  // Signaler qu'il y a de l'espace dans le tampon

        // Consommer le message (afficher)
        printf("Message consommé: %d\n", message);
        sleep(1);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    pthread_t threads[NB_THREADS];
    
    // Initialiser le mutex et les sémaphores
    pthread_mutex_init(&mutexTampon, NULL);
    sem_init(&semVide, 0, 10);  // Le tampon commence plein (10 espaces vides)
    sem_init(&semPlein, 0, 0);   // Le tampon commence vide (0 message)

    int i;
    for (i = 0; i < NB_THREADS; i++) {
        if (i > 0) {
            // Créer un producteur
            if (pthread_create(&threads[i], NULL, &producteur, NULL) != 0) {
                perror("Échec de la création du thread producteur");
            }
        } else {
            // Créer un consommateur
            if (pthread_create(&threads[i], NULL, &consommateur, NULL) != 0) {
                perror("Échec de la création du thread consommateur");
            }
        }
    }

    // Attendre la fin des threads
    for (i = 0; i < NB_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Échec de l'attente du thread");
        }
    }

    // Détruire les sémaphores et mutex
    sem_destroy(&semVide);
    sem_destroy(&semPlein);
    pthread_mutex_destroy(&mutexTampon);

    return 0;
}

