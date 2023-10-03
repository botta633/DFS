#include "serializer.h"
#include <stddef.h>
#include <stdlib.h>
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include "./infra/send.h"
#include "./infra/receive.h"
#include <string.h>


#define stringize(x) #x

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
    //Don't forget to check where to free
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

ssize_t dfs_read(int fd, void *buff, size_t length) {
    
    struct buffer *buffer = malloc(sizeof(struct buffer));
    buffer->offset = 0;
    strncpy(buffer->buf+buffer->offset++, READ_SEQ, 1);
    strncpy(buffer->buf+buffer->offset++, stringize(fd), 1);
    strncpy(buffer->buf+buffer->offset, stringize(length), 
	    strlen(stringize(length)));

    buffer->offset += strlen(stringize(length));

    buffer->buf[buffer->offset] = '\0';

    block_send(buffer->buf, "127.0.0.1", 1234);

    block_receive(buff, "127.0.0.1", 1234);

    return 0;
}


ssize_t dfs_write(int fd, void *buff, size_t length) {
    
    struct buffer *buffer = malloc(sizeof(struct buffer));
    buffer->offset = 0;
    strncpy(buffer->buf+buffer->offset++, WRITE_SEQ, 1);
    strncpy(buffer->buf+buffer->offset++, stringize(fd), 1);
    memcpy(buffer->buf+buffer->offset, buff, length);
    buffer->offset += length;
    strncpy(buffer->buf+buffer->offset, stringize(length), 
	    strlen(stringize(length)));

    buffer->offset += strlen(stringize(length));

    buffer->buf[buffer->offset] = '\0';

    block_send(buffer->buf, "127.0.0.1", 1234);

    block_receive(buff, "127.0.0.1", 1234);

    return 0;
}










int main(){
    dfs_open("let's sfsafsao", '1');


    return 0;
}

