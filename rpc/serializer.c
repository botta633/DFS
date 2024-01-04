#include "serializer.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include "./infra/send.h"
#include "./infra/receive.h"
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

ssize_t serialize_open(const char *path, char flags){
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

static int convert_to_str(char *buf, int x){
    int count = 0;

    while(x) {
        buf[count++] = (char)x%10;
        x = x/10;
    };

    int l = 0;
    int r = count;

    while(l < r) {
        char temp = buf[l];
        buf[l] = buf[r];
        buf[r] = temp;
        l++;
        r++;
    }

    return count;
}

ssize_t serialize_read(int fd, void *buff, size_t length) {

    struct buffer *buffer = malloc(sizeof(struct buffer));
    memset(buffer, 0, sizeof(struct buffer));
    buffer->offset = 0;
    char fdstr [10];

    strncpy(buffer->buf+buffer->offset++, READ_SEQ, 1);
    // limitation fd should be [0:255]
    buffer->buf[buffer->offset++] = fd%256;
    strncpy(buffer->buf+buffer->offset, (char *)(&length), sizeof(length)); 
    buffer->offset += sizeof(length);
    printf("size of length = %d\n", sizeof(length));
    printf("came here\n");
    buffer->buf[buffer->offset] = '\0';
    printf("%d\n", *(int *)(buffer->buf + 2));

    block_send(buffer->buf, "127.0.0.1", 1234);
    block_receive(buff, "127.0.0.1", 1234);

    free(buffer);
    return 0;
}


ssize_t serialize_write(int fd, void *buff, size_t length) {

    struct buffer *buffer = malloc(sizeof(struct buffer));
    buffer->offset = 0;
    char fd_str [10];
    int count = convert_to_str(fd_str, fd);

    strncpy(buffer->buf+buffer->offset++, WRITE_SEQ, 1);
    strncpy(buffer->buf+buffer->offset++,fd_str, count);
    memcpy(buffer->buf+buffer->offset, buff, length);
    buffer->offset += length;
    buffer->buf[buffer->offset++] = '\0';

    // no need to copy length, can be deduced from the null terminator on server side   
    block_send(buffer->buf, "127.0.0.1", 1234);
    block_receive(buff, "127.0.0.1", 1234);

    return sizeof(buff);
}




int main(){
    char buff[5] = "wrwq";
    serialize_read(3, buff, 4);


    return 0;
}

