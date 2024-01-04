#include "task_manager.h"
#include <stdlib.h>
#include <unistd.h>
#include "../rpc/serializer.h"
#include "../rpc/deserializer.h"



 Task *create_task(char *data)
{
    Task *task = malloc(sizeof (Task));
    
    if(!task)
        return NULL;


    switch (data[0]) {
        case OPEN_SEQ:
            task->thread_func = open_task;
            break;
        case READ_SEQ:
            task->thread_func = read_task;
            break;
        case WRITE_SEQ:
            task->thread_func = write_task;
            break;

    }

    task->args = data;

    return 0;
}

void read_task(char *data) {
    read_args *args = deserialize_read(data);
    read(args->fd, args->buff, args->length);
    char *content = args->buff;



}

    



