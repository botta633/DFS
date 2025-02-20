#ifndef __TASK_MANAGER_H
#define __TASK_MANAGER_H


typedef void (*func)(char *);

typedef struct task {
    func thread_func;
    char *args;
}Task;

Task *create_task(void *args);


#endif // !__TASK_MANAGER_H
#define __TASK_MANAGER_H

