/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-23
  Version:0.1.0
*/

#include "../lib/help.h"
#include <time.h>

int main(int argc, char **argv){
	int listenfd = -1, connfd;
	struct sockaddr_storage cliaddr;
	char buf[MAXLINE];
	time_t ticks;
	socklen_t len;

	if(argc == 2){
		listenfd = Tcp_listen(NULL,argv[1], &len);
	} else if(argc == 3){
		listenfd = Tcp_listen(argv[1],argv[2],&len);
	} else {
		err_quit("usage: daytime [ <host> ] <service or port>");
	}
		
	for(;;){
		len = sizeof(cliaddr);
		connfd = Accept(listenfd,(SA*)&cliaddr,&len);
		printf("connect from %s\n", Sock_ntop((SA*)&cliaddr,len));

		ticks=time(NULL);
		snprintf(buf,sizeof(buf),"%.24s\r\n",ctime(&ticks));
		Writen(connfd,buf,strlen(buf));
		Close(connfd);
	}
	Close(listenfd);
	return 0;
}
