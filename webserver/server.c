#include "server.h"

int main(int argc,char *argv[]){
    int sfd,cfd;
    IPv4 client;
    socklen_t  cli_len;
    char s_IP[32];

    sfd=s_sock(8080);
    if(sfd==-1) return -1;

    listen(sfd,4);//Passive connection
    while(1){
        /*Take out one connection*/       
        cli_len=sizeof(client);
        cfd=accept(sfd,(IP *)&client,&cli_len);
        if(cfd==-1){
            perror("accept");
            return -1;
        }
        printf("%s\n",inet_ntop(AF_INET,&client.sin_addr,s_IP,32));
        pid_t pid=fork();
        if(pid==-1){
            perror("fork");
            return -1;
        }
        if(pid==0){
            close(sfd);
            /*Business process*/
            doit(cfd);
            close(cfd);
            exit(0);
        }else{
            close(cfd);
            waitpid(-1,NULL,WNOHANG);
        }

    }
    return 0;
}

