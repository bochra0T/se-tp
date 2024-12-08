#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Pour sleep()

// Variable partagée
int shared_variable = 0;

// Mutex pour synchronisation
pthread_mutex_t lock;

// Fonction pour incrémenter la variable partagée
void* increment_variable(void* arg) {
    for (int i = 0; i < 10; i++) {
        // Verrouiller avant d'accéder à la variable partagée
        pthread_mutex_lock(&lock);
        shared_variable++;
        printf("Thread Incrément : Valeur incrémentée = %d\n", shared_variable);
        pthread_mutex_unlock(&lock); // Déverrouiller
        sleep(1); // Pause pour simuler un traitement
    }
    return NULL;
}

// Fonction pour afficher la valeur de la variable partagée
void* display_variable(void* arg) {
    for (int i = 0; i < 10; i++) {
        // Verrouiller avant d'accéder à la variable partagée
        pthread_mutex_lock(&lock);
        printf("Thread Affichage : Valeur actuelle = %d\n", shared_variable);
        pthread_mutex_unlock(&lock); // Déverrouiller
        sleep(1); // Pause pour simuler un traitement
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialisation du mutex
    pthread_mutex_init(&lock, NULL);

    // Création des threads
    pthread_create(&thread1, NULL, increment_variable, NULL);
    pthread_create(&thread2, NULL, display_variable, NULL);

    // Attente de la fin des threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destruction du mutex
    pthread_mutex_destroy(&lock);

    printf("Programme terminé.\n");
    return 0;
}
