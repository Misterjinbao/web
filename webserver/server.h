#ifndef SERVER_H_
#define SERVER_H_
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
/*Type definition*/
typedef struct sockaddr IP;
typedef struct sockaddr_in IPv4;

int s_sock(int);

#endif
