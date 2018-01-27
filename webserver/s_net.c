#include "server.h"

int s_sock(int port){
    int sfd;
    IPv4 serv;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1){
        perror("socket");
        return -1;
    }
    /*Initialize Memberl of serv*/
    serv.sin_family=AF_INET;
    serv.sin_port=htons(port);
    serv.sin_addr.s_addr=htonl(INADDR_ANY);
    /*Binding IP and port*/
    int b=bind(sfd,(IP *)&serv,sizeof(serv));
    if(b==-1){
        perror("bind");
        return -1;
    }
    return sfd;
}

