#include "queue.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <unistd.h>


int create_queue(queue_t *queue) {

    queue = malloc(sizeof(struct queue));
    if(!queue)
        return -1;

    queue->head = malloc(sizeof(node_t));
    queue->tail = queue->head;

    pthread_mutex_init(&(queue->head_mutex), NULL);
    pthread_mutex_init(&(queue->tail_mutex), NULL);
    pthread_cond_init(&queue->cv, NULL);

    return 0;
}

static int isEmpty(queue_t *queue) {
    return queue->tail->next == NULL;
}

int enqueue(queue_t *queue, void *data) {
    node_t *new_node = malloc(sizeof(node_t));

    if(!new_node)
        return -1;

    pthread_mutex_lock(&(queue->tail_mutex));
    queue->tail->data = data;
    queue->tail->next = new_node;
    queue->tail = new_node;
    pthread_mutex_unlock(&(queue->tail_mutex));
    if(isEmpty(queue))
        pthread_cond_signal(&queue->cv);

    return 0;
}

void *dequeue(queue_t *queue) {

    pthread_mutex_lock(&queue->head_mutex);

    while (queue->head == sentinel) {
        pthread_cond_wait(&queue->cv, &queue->head_mutex);
    }

    node_t *temp = queue->head;
    Task *task = (queue->head->task);
    queue->head = queue->head->next;
    free(temp);

    pthread_mutex_unlock(&(queue->head_mutex));

    return task;

}



