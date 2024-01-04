#include "send.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/_endian.h>
#include <sys/socket.h>

#define SA struct sockaddr

void block_send(char *data, const char *destIP, const int portNum){
    int sockfd, connfd;

    struct sockaddr_in serv_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(portNum),
        .sin_addr.s_addr = inet_addr(destIP),
    };
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(connect(sockfd, (SA *)&serv_addr, sizeof(serv_addr)) != 0) {
        printf("Can't connect to server\n");
        exit(0);
    }
    printf("[+] Connected to server at address %s\n", destIP);
    printf("Data is %s\n", data);
    for(;;) {
        write(sockfd, data, strlen(data)); 
        bzero(data, strlen(data));
        read(sockfd, data, strlen(data));
    }

}



