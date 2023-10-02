#include "queue.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <unistd.h>


static node_t *sentinel = NULL;

int create_queue(queue_t *queue){

    queue = malloc(sizeof(struct queue));
    if(!queue)
	return -1;
    
    node_t *sentinel = malloc(sizeof(node_t));
    if(!sentinel)
	return -1;

    sentinel->next = NULL;
    queue->head = queue->tail = sentinel;
    pthread_mutex_init(&(queue->mutex), NULL);
    pthread_cond_init(&queue->cv, NULL);

    return 0;
}
static int isEmpty(queue_t *queue){
    return queue->head == sentinel;
}
int enqueue(queue_t *queue, Task *task){
    node_t *temp = malloc(sizeof(node_t));
    if(!temp)
	return -1;
    
    temp->task = task;

    pthread_mutex_lock(&(queue->mutex));

    if(isEmpty(queue)){
	queue->head = temp;
	queue->tail = temp;
	queue->tail->next = NULL;
	queue->head->next = NULL;
	pthread_cond_signal(&queue->cv);
	pthread_mutex_unlock(&(queue->mutex));
	return 0;
    }

    queue->tail->next = temp;
    queue->tail= temp;
    queue->tail->next = NULL;

    pthread_mutex_unlock(&(queue->mutex));

    return 0;
}

Task *dequeue(queue_t *queue) {


    pthread_mutex_lock(&queue->mutex);
    
    while (isEmpty(queue)) {
	pthread_cond_wait(&queue->cv, &queue->mutex);
    }
    

    node_t *temp = queue->head;
    Task *task = (queue->head->task);
    queue->head = queue->head->next;
    free(temp);

    pthread_mutex_unlock(&(queue->mutex));

    return task;

}




