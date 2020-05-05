#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

pthread_mutex_t m;
bool teaIsReady = false;        // the condition variable?

void *me(void *arg) {
    
    (void)arg;
    printf("Me: I am waiting for my tea…\n");
    pthread_mutex_lock(&m);
    while(!teaIsReady) {
        pthread_mutex_unlock(&m);
        printf("Me: Still no tea… guess I’ll do nothing\n");    // i guess this loops continually until the teaIsReady
        pthread_mutex_lock(&m);
    }
    pthread_mutex_unlock(&m);
    printf("Me: The condition changed, teaIsReady, and this print statement can now execute.\n");

    return NULL;
}

void *teaRobot(void *arg) {
    (void) arg;
    printf("Robot: I’m making the tea…\n");
    usleep(rand());
    pthread_mutex_lock(&m);
    teaIsReady = true;
    pthread_mutex_unlock(&m);
    printf("Robot: The tea is ready and i’ve updated the variable.");
    return NULL;
}

int main() {

    pthread_t t1, t2;
    int err;

    err = pthread_mutex_init(&m, NULL);        // initialize the mutex we made, passing NULL (???)
    assert(err == 0);
    err = pthread_create(&t1, NULL, me, NULL);
    assert(err == 0);
    err = pthread_create(&t2, NULL, teaRobot, NULL);
    assert(err == 0);
    err = pthread_join(t1, NULL);
    assert(err == 0);
    err = pthread_join(t2, NULL);
    assert(err == 0);
    pthread_mutex_destroy(&m);

}
