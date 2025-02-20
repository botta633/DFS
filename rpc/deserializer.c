#include "./infra/receive.h"
#include "./infra/send.h"
#include "deserializer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_endian.h>

// free the memory returned from all these functions
static void* (*func_mapper[15])(const char*);
open_args *deserialize_open(const char *data){
    open_args *args = malloc(sizeof(open_args));
    int i = 1;
    char path[256];

    while(data[i] != '\0') {
        path[i-1] = data[i];
        i++;
    }

    int flag = path[i-2] - '0';
    args->flags  = flag;
    memcpy(args->path, path, strlen(path));

    return args;

}

read_args *deserialize_read(const char *data){
    read_args *args = malloc(sizeof(read_args));
    int fd = data[1];
    uint32_t length = ntohl(*(uint32_t *)((void *)(data+2)));

    printf("Came here\n");

    printf("fd = %d\n", fd);
    printf("length = %d\n", length);

    return args;
}

write_args *deserialize_write(const char *data){
    write_args *args = malloc(sizeof(write_args));
    int i = 1;
    args->fd = data[i++];
    char buff[256];
    char length[3]; 
    while(data[i] != '\0') {
        buff[i-2] = data[i];
        i++;
    }
    i++;
    int j = 0;
    while(data[i] !=  '\0')
        length[j++] = data[i++];

    printf("came here and data is %s \n", length);
    args->length = atoi(length);
    args->buff = buff;
            return args;
}

void *deserialize(const char *data) {
    printf("came here\n");
    void *args = func_mapper[data[0]](data);
    return args;
}

void init_deserializer()
{   
    func_mapper[1] = (void *)&*deserialize_open;
    func_mapper[2] = (void *)&deserialize_read;
    func_mapper[3] = (void *)&deserialize_write;
}

