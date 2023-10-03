#ifndef __DESERIALIZE_H
#define __DESERIALIZE_H



#include <stddef.h>
#include <sys/_types/_ssize_t.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct read_args {
    int fd;
    void *buff;
    size_t length;
} read_args;


typedef struct write_args {
    int fd;
    void *buff;
    size_t length;
} write_args;

typedef struct open_args {
    char path[256];
    int flags;
} open_args;


read_args *deserialize_read(const char *data);
write_args *deserialize_write(const char *data);
open_args *deserialize_open(const char *data);






#endif
