#include "./infra/receive.h"
#include "deserializer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
    int fd = (int)(data[0]);
    args->fd = fd;

    //limitation of size in read
   
    args->length = (int)(data[1]);
    return args;
}

write_args *deserialize_write(const char *data)




int main() {

    char arr[4096];

    block_receive(arr, "127.0.0.1", 1234);

    deserialize_open(arr);
    return 0;
}
