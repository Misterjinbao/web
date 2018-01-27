#include"server.h"
typedef struct request{
    char method[16];
    char path[256];
    char proto[16];
}req_t;

typedef struct response{
    int code;//404   200
    char *f_type;
    req_t *req;
}res_t;

char *decl_dir="/home/tarena/html";

static void get_request(int fd,req_t *rq){
    char buf[512];
    char path[256];
    int r=read(fd,buf,512);
    write(1,buf,r);
    sscanf(buf,"%s %s %s\r\n",\
            rq->method,rq->path,rq->proto);
    if(strcmp(rq->path,"/")==0)
        strcpy(rq->path,"/index.html");
    strcpy(path,decl_dir);
    strcat(path,rq->path);
    strcpy(rq->path,path);
    printf("requset path:%s\n",rq->path);
    return;
}

static void response_b_404(int fd){
    char *f_line="HTTP/1.1 404\r\n";
    char *cont="Content-type: text/html\r\n\r\n";
    char *html="<html><body>file not found...!</body></html>";
    write(fd,f_line,strlen(f_line));
    write(fd,cont,strlen(cont));
    write(fd,html,strlen(html));
    return;
}
static char *get_ftype(const char *p){
    if(strcmp(strrchr(p,'.'),".html")==0)return "text/html";
    if(strcmp(strrchr(p,'.'),".jpg")==0)return "image/jpg";
    if(strcmp(strrchr(p,'.'),".png")==0)return "image/png";
    if(strcmp(strrchr(p,'.'),".mp3")==0)return "video/mp3";
    if(strcmp(strrchr(p,'.'),".mp4")==0)return "video/mp4";
    return "text/html";

}
static void do_client(res_t *rs){
    rs->code=access(rs->req->path,R_OK)? 404:200;
    rs->f_type=get_ftype(rs->req->path);
    return;
}
static void response_b_200(int fd,res_t *rs){
    char f_line[128];
    char content[128];
    sprintf(f_line,"%s %d\r\n",rs->req->proto,rs->code);
    sprintf(content,"Content-Type: %s\r\n\r\n",rs->f_type);
    dup2(fd,1);//Redirect output to browser
    write(1,f_line,strlen(f_line));
    write(1,content,strlen(content));
    execlp("cat","cat",rs->req->path,NULL);
    return;
}
static void response_b(int fd,res_t *rs){
    if(rs->code==404)
        response_b_404(fd);
    else
        response_b_200(fd,rs);
    return;
}

void doit(int fd){
    req_t req;
    res_t res;
    /*Read data from client*/
    get_request(fd,&req);
    res.req=&req;
    /*Processing data*/
    do_client(&res);
    /*Responding client*/
    response_b(fd,&res);
    return;

}

