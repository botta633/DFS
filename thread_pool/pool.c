#include "pthread.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_cond_t.h>
#include <unistd.h>
#include "pool.h"
#include "queue.h"


static queue_t *queue;
pthread_t threads[MAX_POOL_CAPACITY];



void *consume_func(void *args) {

    while(1) {
        execute();
    }
    return NULL;
}

void init_pool(){

    //init task queue
    if(create_queue(queue) == -1)
        exit(0);

    for(int i = 0; i < MAX_POOL_CAPACITY; i++)
        pthread_create(&threads[i], NULL, consume_func, NULL);
}

void add_task(Task *task){
    enqueue(queue, task);
}

int execute(){
    Task *func = dequeue(queue);
    func->thread_func(func->args);
    return 0;
}

