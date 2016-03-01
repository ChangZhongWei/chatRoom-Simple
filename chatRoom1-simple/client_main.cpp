/*************************************************************************
    > File Name: client_main.cpp
    > Author:czw
    > Mail:changzhongwei3@163.com 
    > Created Time: Thu 21 May 2014 06:12:43 AM PDT
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "wrap_func.h"

void deal_msg(int sockfd);

//client   /////////////////
int main(int argc, char *argv[])
{
	//设置 ip:port
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n",  argv[0] ) ;
        return 1;
    }

    const char* serv_inet_addr = argv[1];
    int port = atoi( argv[2] );
    int client_connfd;
    if((client_connfd = Open_clientfd(serv_inet_addr, port)) < 0)
        return 0;
    
//	deal_msg(client_connfd);
    printf("connect success!\n");
	close(client_connfd);
	return 0;
//_
}


void deal_msg(int sockfd)
{
    return;
	//char buff[MAXLINE] = "";
	int msg_len = 0;
	//cout << "input data:";
	while(true )
	{
	//	cin >> buff;
	//	write(sockfd, buff, strlen(buff));
	//	cout << endl;
	//	cout << "input data:";
	}
}
