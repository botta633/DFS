#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define IP_ADDR "127.0.0.1"
#define SA struct sockaddr



int main(){

  int sockfd = socket(AF_INET,SOCK_STREAM, 0); 

  struct sockaddr_in serv_addr = {
    .sin_addr.s_addr = inet_addr(IP_ADDR),
    .sin_port = htons(1234),
    .sin_family = AF_INET,
  };



  if(connect(sockfd, (SA *)&serv_addr, sizeof(serv_addr) != 0)){
      printf("Can't connect to server \n");
      exit(0);
  }




}





