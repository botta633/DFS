#ifndef __SEND_H
#define __SEND_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void block_send(char *data, const char *destIP, const int portNum);





#endif
