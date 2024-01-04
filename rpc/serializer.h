#ifndef __RPC_H
#define __RPC_H

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

#define RONLY "0"
#define RW "1"

#define OPEN_SEQ '1'
#define READ_SEQ '2'
#define WRITE_SEQ '3'
struct buffer {
    char buf[4096];
    int offset;
};

ssize_t dfs_open(const char *path, char flags); 
ssize_t dfs_read(int, void *, size_t);
ssize_t dfs_write(int, void *, size_t);







#endif
