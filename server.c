#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "./thread_pool/pool.h"
#include  "./rpc/infra/receive.h"
#include "./rpc/deserializer.h"
#include <pthread.h>
#define IP_ADDR "127.0.0.1"
#define PORT_NUM 1234


#define SA struct sock_addr



int main() {

    char arr[4096];
    initialize_server();
    init_deserializer();
    for(;;) {
        block_receive(arr, "127.0.0.1", 1234);
        printf("Came here \n");
        add_stream(arr);
    }
    printf("came here\n");

return 0;
}
