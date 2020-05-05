#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <assert.h>

int randInt() {
    return (rand() % 50) + 50;
}

struct BoundedBuffer {
    int start, end, size;
    int *buffer;
    pthread_mutex_t m;
    pthread_cond_t add_cv;
    pthread_cond_t remove_cv;

}; 

typedef struct BoundedBuffer BoundedBuffer;

BoundedBuffer * createBoundedBuffer(int size) {
    BoundedBuffer *bb = malloc(sizeof(BoundedBuffer));
    bb->size = size;
    bb->start = 0;
    bb->end = size-1;
    bb->buffer = malloc(sizeof(int) * size);

    pthread_mutex_init(&bb->m, NULL);
    pthread_cond_init(&bb->add_cv, NULL);
    pthread_cond_init(&bb->remove_cv, NULL);

    return bb;
}


void destroyBoundedBuffer(BoundedBuffer *bb) {
    
    pthread_mutex_destroy(&bb->m);
    pthread_cond_destroy(&bb->add_cv);
    pthread_cond_destroy(&bb->remove_cv);

    free(bb->buffer);
    free(bb);
}


void addItem(BoundedBuffer *bb, int item) {
    if (!bb) {
        return;
    }
    pthread_mutex_lock(&bb->m);
    while (bb->start == bb->end) {
        printf("== Buffer is full ==\n");
        pthread_cond_wait(&bb->add_cv, &bb->m);
    }

    bb->buffer[bb->start] = item;
    bb->start = (bb->start + 1) % bb->size;
    
    pthread_mutex_unlock(&bb->m);
    pthread_cond_signal(&bb->remove_cv);

}


int removeItem(BoundedBuffer *bb) {
    if (!bb) {
        assert(0);
    }
    pthread_mutex_lock(&bb->m);
    while ( ((bb->end + 1) % bb->size) == bb->start ) {
        printf("== Buffer is empty ==\n");
        pthread_cond_wait(&bb->remove_cv, &bb->m);
    }

    bb->end = (bb->end + 1) % bb->size;
    int item = bb->buffer[bb->end];
    pthread_mutex_unlock(&bb->m);
    pthread_cond_signal(&bb->add_cv);
    return item;

}


void * producer(void *arg) {
    BoundedBuffer *bb = (BoundedBuffer *)arg;
    for (int i = 0; i < 10; i++) {
        int item = randInt();
        printf("produced item %d\n", item);
        addItem(bb, item);
        usleep(randInt());
    }
    return NULL;
}

void * consumer(void *arg) {
    BoundedBuffer *bb = (BoundedBuffer *)arg;
    for (int i = 0; i < 10; i++) {
        int item = removeItem(bb);
        printf("    consumed item %d\n", item);
        usleep(randInt());
    }
    return NULL;
}



int main() {

    srand(time(NULL));
    pthread_t t1;
    pthread_t t2;
    int err;

    BoundedBuffer *bb = createBoundedBuffer(4);


    err = pthread_create(&t1, NULL, consumer, bb);
    assert(err == 0);

    err = pthread_create(&t2, NULL, producer, bb);
    assert(err == 0);

    err = pthread_join(t1, NULL);
    assert(err == 0);
    err = pthread_join(t2, NULL);
    assert(err == 0);

}
