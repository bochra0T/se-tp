#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int value_globale = 1;

void* increment(void* arg) {
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);
        value_globale++;
        pthread_mutex_unlock(&mutex); 
    }
    return NULL;
}

void* decrement(void* arg) {
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex); 
        value_globale--;
        pthread_mutex_unlock(&mutex); 
    }
    return NULL;
}

int main() {
    pthread_t th,th2;
     pthread_mutex_init(&mutex, NULL);
     
     
    
    pthread_create(&th, NULL, increment, NULL);
    pthread_create(&th2, NULL, decrement, NULL);
   // printf("thread stareted %d",i);
     printf("\n");


    // Wait for threads to finish
 
        pthread_join(th, NULL);
          pthread_join(th2, NULL);
        //   printf("thread finich  %d ",i);
           printf("\n");
    
    
    pthread_mutex_destroy(&mutex);

    printf("Valeur value_globale : %d\n", value_globale);

    return 0;
}
