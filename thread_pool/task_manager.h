#ifndef __TASK_MANAGER_H
#define __TASK_MANAGER_H


typedef void (*func)(char *);

typedef struct task {
    func thread_func;
    char *args;
}Task;

Task *create_task(char *data);


void read_task(char *data);
void write_task(char *data);
void open_task(char *data);

#endif // !__TASK_MANAGER_H
#define __TASK_MANAGER_H

