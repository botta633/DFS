#include "task_manager.h"
#include <stdlib.h>
#include <unistd.h>

 Task *create_task(void *args)
{
    Task *task = malloc(sizeof (Task));
    
 
    task->args = args;

    return args;
}

