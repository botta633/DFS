
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_cond_t.h>
#include <unistd.h>
#include "pool.h"
#include "queue.h"
#include "task_manager.h"
#include "../rpc/deserializer.h"


static queue_t *task_queue;
static queue_t *data_queue;
pthread_t worker_threads[MAX_POOL_CAPACITY];
pthread_t assembly_line_threads[3];

void *consume_func(void *args) {

    while(1) {
        execute();
    }
    return NULL;
}

void *help(void *args) {

    while(1) {
        create_task_helper();
    }

    return NULL;
}

void init_pool(){

    //init task queue
    if(create_queue(task_queue) == -1)
        exit(0);

    if(create_queue(data_queue) == -1)
        exit(0);

    for(int i = 0; i < MAX_POOL_CAPACITY; i++)
        pthread_create(&worker_threads[i], NULL, consume_func, NULL);

    for(int i = 0; i < 3; i++)
        pthread_create(&assembly_line_threads[i], NULL, help, NULL);
}


int execute(){
    Task *func = dequeue(task_queue);
    func->thread_func(func->args);
    return 0;
}


void add_stream(const char *data) {
    enqueue(data_queue, data);
    printf("came here\n");
}

int create_task_helper() {

    const char *data = dequeue(data_queue);

    printf("came here\n");
    void *args = deserialize(data);
    Task *task = create_task(args);
    enqueue(task_queue, task);
    return 0;

}



