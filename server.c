#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "./thread_pool/pool.h"
#include  "./rpc/infra/receive.h"
#define IP_ADDR "127.0.0.1"
#define PORT_NUM 1234


#define SA struct sock_addr


int main(){
    
    initialize_server();
    
}









    return 0;
}
