/*************************************************************************
    > File Name: server_main.cpp
    > Author:czw
    > Mail:changzhongwei3@163.com 
    > Created Time: Thu 21 May 2014 07:05:27 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "wrap_func.h"
void deal_msg(int sockfd);

int main(int argc, char *argv[])
{
	// 设置 ip:port	
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n",  argv[0] );
        return 1;
    }
    const char* serv_inet_addr = argv[1];
    int port = atoi( argv[2] );

	int listenfd, connfd;

    if((listenfd=Open_listenfd(port)) < 0)
    {
        printf("listenfd fail!\n");
        return 0;
    }
    struct sockaddr_in serveraddr;
    int ret = assemble_addr(serv_inet_addr, port, &serveraddr);
    if(ret == 2)
    {
        printf("assemble_addr error!\n");
        return 1;
    }
	socklen_t sock_len = sizeof(serveraddr);
    connfd = Accept(listenfd, (struct sockaddr*)&serveraddr, &sock_len);
    if(connfd >= 0)
        printf("connect success\n");
    
	close(listenfd);
    return 0;

	while(1)
	{
		connfd = Accept(listenfd, (struct sockaddr*)&serveraddr, &sock_len);
	// accept
		//deal_msg(connfd);
		close(connfd);
	}
	close(listenfd);
	return 0;

}

void deal_msg(int sockfd)
{
	char buff[MAXLINE] = "";
	int msg_len = 0;
	while( (msg_len = read(sockfd, buff, MAXLINE-1)) > 0 ) 
	{
		buff[msg_len] = 0;
		printf("%s \n");
	}
}
