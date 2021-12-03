/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-19
  Version:0.1.0
*/

#include "../lib/help.h"

int main(int argc,char **argv){
	struct sockaddr_in saddr,caddr;
	char recvbuf[MAXLINE];
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	saddr.sin_port=htons(8080);
	saddr.sin_family=AF_INET;
	int listenfd = Socket(AF_INET,SOCK_DGRAM,0);
	Bind(listenfd,(SA*)&saddr,sizeof(saddr));
	for(;;){
		socklen_t len=sizeof(caddr);
		memset(recvbuf,0,MAXLINE);
		int readn = Recvfrom(listenfd,recvbuf,sizeof(recvbuf),0,(SA*)&caddr,&len);
		printf("connect form %s:%d,recv %d byets\n",inet_ntoa(saddr.sin_addr),ntohs(caddr.sin_port),readn);
		Sendto(listenfd,recvbuf,strlen(recvbuf),0,(SA*)&caddr,sizeof(caddr));
	}
	Close(listenfd);
	return 0;
}
