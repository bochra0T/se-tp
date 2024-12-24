#include <stdio.h>
#include <pthread.h>

int premi[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int results[2];

void* some(void* arg) {
    int index = *(int*)arg;//pour changi le tyoe de variabl 
    int somme = 0;

    for (int j = 0; j < 5; j++) {
        somme += premi[index + j];
    }

    results[index / 5] = somme;
    return NULL;
}

int main() {
    pthread_t thread[2];
    int indices[2] = {0, 5};

    for (int i = 0; i < 2; i++) {
        pthread_create(&thread[i], NULL, some, &indices[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(thread[i], NULL);
    }

    for (int i = 0; i < 2; i++) {
        printf("نتيجة الخيط %d: %d\n", i, results[i]);
    }

    return 0;
}
