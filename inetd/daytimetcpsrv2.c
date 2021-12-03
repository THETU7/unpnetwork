/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-27
  Version:0.1.0
*/

#include "../lib/help.h"
#include <time.h>

int main(int argc, char **argv){
	if(argc < 2 || argc >3 )
		err_quit("usage: daytimetcpsrv2 [<host>] <service or port>");

	int listenfd,connfd;
	struct sockaddr *cliaddr;
	socklen_t addrlen,len;
	char buff[MAXLINE];
	daemon_init(argv[0],0);
	
	if(argc==2)
		listenfd = Tcp_listen(NULL,argv[1],&addrlen);
	else 
		listenfd = Tcp_listen(argv[1],argv[2],&addrlen);

	cliaddr = Malloc(addrlen);

	for(;;){
		len = addrlen;
		connfd = Accept(listenfd,cliaddr,&len);
		err_msg("connection from %s",Sock_ntop(cliaddr, len));

		time_t trick=time(NULL);

		snprintf(buff,MAXLINE,"%.24s\r\n", ctime(&trick));
		Writen(connfd,buff,strlen(buff));

		Close(connfd);
	}
	free(cliaddr);
	Close(listenfd);
	return 0;
}
