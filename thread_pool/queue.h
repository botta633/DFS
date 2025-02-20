#ifndef __QUEUE_H
#define __QUEUE_H
#include <pthread.h>
#include <sys/_pthread/_pthread_cond_t.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include "task_manager.h"

typedef struct Node {
    void *data;
    struct Node *next;
} node_t;


typedef struct queue{
    node_t *head;
    node_t *tail;
    pthread_mutex_t head_mutex;
    pthread_mutex_t tail_mutex;
    pthread_cond_t cv;
} queue_t;


int create_queue(queue_t *queue);
int enqueue(queue_t *queue, void *task);
void *dequeue(queue_t *queue);
static int isEmpty(queue_t *queue);





#endif
