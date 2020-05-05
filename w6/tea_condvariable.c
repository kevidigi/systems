#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

pthread_mutex_t m;

pthread_cond_t cv;              // condiiton variable is a distinct type

bool teaIsReady = false;        // i was wrong, this is not the condition variable - rather, this is the condition

void *me(void *arg) {
    
    (void)arg;
    pthread_mutex_lock(&m);
    while(!teaIsReady) {
        pthread_mutex_unlock(&m);
        printf("Me: I am waiting for the tea to be ready... just once, I think.\n");    // i think this runs once, 'til teaIsReady
        pthread_cond_wait(&cv, &m);
    }
    pthread_mutex_unlock(&m);
    printf("Me: The condition changed, teaIsReady, and this print statement can now execute.\n");
    printf("Me: Just gonna check (for some reason), is the tea definitely ready? %s\n", teaIsReady ? "Yes." : "No.");
    pthread_mutex_unlock(&m);

    return NULL;
}

void *teaRobot(void *arg) {
    (void) arg;
    printf("Robot: I’m making the tea…\n");
    usleep(rand());

    pthread_mutex_lock(&m);
    teaIsReady = true;
    pthread_mutex_unlock(&m);

    pthread_cond_signal(&cv);

    printf("Robot: The tea is ready and i’ve updated the variable, but more importantly I've signalled via the cv.\n");
    return NULL;
}

int main() {

    pthread_t t1, t2;
    int err;

    err = pthread_mutex_init(&m, NULL);        // initialize the mutex we made, passing NULL (???)
    assert(err == 0);

    err = pthread_cond_init(&cv, NULL);         // we need to initalise the condition variable too
    assert(err == 0);

    err = pthread_create(&t1, NULL, me, NULL);
    assert(err == 0);
    err = pthread_create(&t2, NULL, teaRobot, NULL);
    assert(err == 0);
    err = pthread_join(t1, NULL);
    assert(err == 0);
    err = pthread_join(t2, NULL);
    assert(err == 0);
    pthread_cond_destroy(&cv);                  // and destroy the condition variable
    pthread_mutex_destroy(&m);

}
