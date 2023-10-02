#include "serializer.h"
#include <stddef.h>
#include <stdlib.h>
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include "./infra/send.h"
#include <string.h>

//static struct buffer *serialize_read(struct read_args *args){
//    struct buffer *buff = (struct buffer *)(malloc(sizeof(struct buffer)));
//
//    char arr[5];
//
//    char x  = args->fd + '0';
//
//    memcpy(buff->buf, &x, 1);
//
//    x = (char)33;
//    memcpy(buff->buf + 1, &x, 1);
//    return buff;
//
//}

ssize_t dfs_open(const char *path, char flags){
    struct buffer *buffer = malloc(sizeof(struct buffer));
    buffer->offset = 0;
    strncpy(buffer->buf+buffer->offset++, OPEN_SEQ, 1);
    memcpy(buffer->buf+buffer->offset, path, strlen(path)); 
    buffer->offset += strlen(path);
    buffer->buf[buffer->offset++] = flags;
    buffer->buf[buffer->offset++] = '\0';
    block_send(buffer->buf, "127.0.0.1", 1234);

    return 0;
}












int main(){
    dfs_open("let's sfsafsao", '1');


    return 0;
}

