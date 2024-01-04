#ifndef __POOL_H
#define __POOL_H
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "queue.h"


#define MAX_POOL_CAPACITY 10


void add_task(Task *task);
int execute();

void *thread_func(void *args);
void init_pool();






#endif 
