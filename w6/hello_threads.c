#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

void *PrintHelloWorld(void * n) {
    int *num = n;

    for (int i = 0; i < *num; i++) {
        printf("Hello world - from a thread!\n");
    }
    return NULL;
}


int main() {
 
    pthread_t thread;

    int n = 5;

    int error = pthread_create(&thread, NULL, PrintHelloWorld, &n);
    assert(error == 0);
    printf("Created thread...\n");

    error = pthread_join(thread, NULL);
    assert(error == 0);

}
