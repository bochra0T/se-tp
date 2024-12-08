#include <stdio.h>
#include <pthread.h>

void* tache1(void* arg) {
     int tach2 = 1;
    while (tach2) {
        printf("Je suis occupé par tâche 1\n");
        tach2 =0; 
    }
}
void* tache2(void* arg) {
   int tach2 = 1;
    while (tach2) {
        printf("Je suis occupé par tâche 2\n");
        tach2=0; 
    }
}
int main() { 
    pthread_t pthread1, pthread2;

    // Create threads for tache1 and tache2
    pthread_create(&pthread1, NULL, tache1, NULL);
    pthread_create(&pthread2, NULL, tache2, NULL);

    // Wait for both threads to finish
    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);

    return 0;
}
