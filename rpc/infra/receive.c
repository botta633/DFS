#include "receive.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_endian.h>
#include <sys/socket.h>
#include <unistd.h>


#define SA struct sockaddr


void block_receive(char *data, const char *servIP, const int portNum){
    int sockfd, connfd;
    struct sockaddr_in cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr = {
	.sin_addr.s_addr = htonl(INADDR_ANY),
	.sin_family = AF_INET,
	.sin_port = htons(portNum),
    };

    printf("[+] Server started!\n");

    if(bind(sockfd, (SA *)&serv_addr, sizeof(serv_addr)) != 0){
	printf("Cannot bind socket\n");
	exit(0);
    }

    else 
	printf("Successfully binded socket to server\n");

    if(listen(sockfd, 5) != 0){
	printf("Coudlnt' listen to specificed port\n");
	exit(0);
    }

    int len = sizeof(cli);
    connfd = accept(sockfd, (SA *)&cli, &len);

    char receiveBuffer[8000];
    char sendBuffer[4096];
    
    bzero(receiveBuffer, sizeof(receiveBuffer));
    for(;;){
	if(read(connfd, receiveBuffer, 4096) > 0){
	    printf("%s\n", receiveBuffer);
	    memcpy(data, receiveBuffer, strlen(receiveBuffer));
	    return;
	}
}

}


