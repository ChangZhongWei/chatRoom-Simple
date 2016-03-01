/*************************************************************************
 > File Name: server_main.cpp
 > Author:czw
 > Mail:changzhongwei3@163.com
 > Created Time: Thu 21 May 2014 07:15:30 AM PDT
 ************************************************************************/

#ifndef __WRAP_FUNC_H__
#define __WRAP_FUNC_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;

#define RIO_BUFSIZE 8192
typedef struct {
    int rio_fd;                /* descriptor for this internal buf */
    int rio_cnt;               /* unread bytes in internal buf */
    char *rio_bufptr;          /* next unread byte in internal buf */
    char rio_buf[RIO_BUFSIZE]; /* internal buffer */
} rio_t;
/* $end rio_t */

/* Sockets 封装接口 */
int Socket(int domain, int type, int protocol);
void Setsockopt(int s, int level, int optname, const void *optval, int optlen);
void Bind(int sockfd, struct sockaddr *my_addr, int addrlen);
void Listen(int s, int backlog);
int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen);

/* 打印错误信息 */
void unix_error(const char *msg);
void posix_error(int code, const char *msg);
void dns_error(const char *msg);
void app_error(const char *msg);

/* 全局变量 */
extern int h_errno;    /* defined by BIND for DNS errors */ 
extern char **environ; /* defined by libc */

/* Misc constants */
#define	MAXLINE	 8192  /* max text line length */
#define MAXBUF   8192  /* max I/O buffer size */
#define LISTENQ  1024  /* second argument to listen() */
typedef struct sockaddr SA;


int open_clientfd(const char *hostname, int portno);
int open_listenfd(int portno);

int Open_clientfd(const char *hostname, int port);
int Open_listenfd(int port); 

int assemble_addr(const char *hostname, int port, struct sockaddr_in *paddr);


#endif
