/*************************************************************************
 > File Name: server_main.cpp
 > Author:czw
 > Mail:changzhongwei3@163.com
 > Created Time: Thu 21 May 2014 07:15:37 AM PDT
 ************************************************************************/

#include "wrap_func.h"

/** 错误信息 log*/
/* unix-style error */
void unix_error(const char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

/* posix-style error */
void posix_error(int code, const char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}

/* dns-style error */
void dns_error(const char *msg)
{
    fprintf(stderr, "%s: DNS error %d\n", msg, h_errno);
    exit(0);
}

/* application error */
void app_error(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(0);
}

//===========

/** 服务器和客户端封装函数*/
int assemble_addr(const char *hostname, int port, struct sockaddr_in *paddr)
{
    struct hostent *hp;//DNS域名主机入口结构
    if((hp=gethostbyname(hostname)) == NULL)
        return -1;
    bzero((char*)paddr, sizeof(*paddr));
    (*paddr).sin_family = AF_INET;
    bcopy((char *)hp->h_addr_list[0], 
	  (char *)&(*paddr).sin_addr.s_addr, hp->h_length);// look bcopy
    paddr->sin_port = htons(port);
    return 0;
}


/* $打开客户端 */
int open_clientfd(const char *hostname, int port) 
{
    int clientfd;
    struct sockaddr_in serveraddr;

    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;
    int ret = assemble_addr(hostname, port, &serveraddr);
    if(ret < 0)
        return -2;
    /*
    if ((hp = gethostbyname(hostname)) == NULL)
	return -2;//  check h_errno for cause of error
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)hp->h_addr_list[0], 
	  (char *)&serveraddr.sin_addr.s_addr, hp->h_length);
    serveraddr.sin_port = htons(port);*/

    /* Establish a connection with the server */
    if (connect(clientfd, (SA *) &serveraddr, sizeof(serveraddr)) < 0)
        return -1;
    return clientfd;
}


int open_listenfd(int port) 
{
    int listenfd, optval=1;
    struct sockaddr_in serveraddr;
  
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;
 
    /* 让绑定端口重用 */
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, 
		   (const void *)&optval , sizeof(int)) < 0)
        return -1;

    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET; 
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serveraddr.sin_port = htons((unsigned short)port); 
    if (bind(listenfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0)
        return -1;

    //开始监听
    if (listen(listenfd, LISTENQ) < 0)
        return -1;
    return listenfd;
}

/** 准备启动，函数封装*/
int Open_clientfd(const char *hostname, int port) 
{
    int rc;

    if ((rc = open_clientfd(hostname, port)) < 0) {
	if (rc == -1)
	    unix_error("Open_clientfd Unix error");
	else        
	    dns_error("Open_clientfd DNS error");
    }
    return rc;
}

int Open_listenfd(int port) 
{
    int rc;

    if ((rc = open_listenfd(port)) < 0)
        unix_error("Open_listenfd error");
    return rc;
}

/** Sockets 接口函数封装*/
int Socket(int domain, int type, int protocol) 
{
    int rc;

    if ((rc = socket(domain, type, protocol)) < 0)
        unix_error("Socket error");
    return rc;
}

void Setsockopt(int s, int level, int optname, const void *optval, int optlen) 
{
    int rc;

    if ((rc = setsockopt(s, level, optname, optval, optlen)) < 0)
        unix_error("Setsockopt error");
}

void Bind(int sockfd, struct sockaddr *my_addr, int addrlen) 
{
    int rc;

    if ((rc = bind(sockfd, my_addr, addrlen)) < 0)
        unix_error("Bind error");
}

void Listen(int s, int backlog) 
{
    int rc;

    if ((rc = listen(s,  backlog)) < 0)
        unix_error("Listen error");
}

int Accept(int s, struct sockaddr *addr, socklen_t *addrlen) 
{
    int rc;

    if ((rc = accept(s, addr, addrlen)) < 0)
        unix_error("Accept error");
    return rc;
}

void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen) 
{
    int rc;

    if ((rc = connect(sockfd, serv_addr, addrlen)) < 0)
        unix_error("Connect error");
}
