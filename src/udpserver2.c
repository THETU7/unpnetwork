/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-19
  Version:0.1.0
*/

#include "../lib/help.h"
#include <sys/select.h>
#include <unistd.h>

void sigchld(int);

int main(){
	struct sockaddr_in saddr,caddr;
	char buf[MAXLINE];
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	saddr.sin_port=htons(8080);
	saddr.sin_family=AF_INET;
	fd_set sets;
	FD_ZERO(&sets);
	int listenfd=Socket(AF_INET,SOCK_STREAM,0);
	const int on=1;
	Setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	Bind(listenfd,(SA*)&saddr,sizeof(saddr));
	Listen(listenfd,LISTENQ);
	int udpfd=Socket(AF_INET,SOCK_DGRAM,0);
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	saddr.sin_port=htons(8080);
	saddr.sin_family=AF_INET;
	Bind(udpfd,(SA*)&saddr,sizeof(saddr));
	int maxfd1 = listenfd>udpfd?listenfd:udpfd;
	Signal(SIGCHLD, sigchld);
	for(;;){
		FD_SET(listenfd,&sets);
		FD_SET(udpfd,&sets);
		if(select(maxfd1+1,&sets,NULL,NULL,NULL)<0){
			if(errno==EINTR)
				continue;
			else 
				err_sys("slecet error");
		}
		if(FD_ISSET(udpfd,&sets)){
			socklen_t len = sizeof(caddr);
			int nread = Recvfrom(udpfd,buf,MAXLINE,0,(SA*)&caddr,&len);
			printf("connect from %s:%d with udp,recvide %d bytes\n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port),nread);
			Sendto(udpfd,buf,strlen(buf),0,(SA*)&caddr,sizeof(caddr));
			memset(buf,0,strlen(buf));
		}

		if(FD_ISSET(listenfd,&sets)){
			socklen_t len = sizeof(caddr);
			int accpectfd=Accept(listenfd,(SA*)&caddr,&len);
			if(Fork()==0){
				Close(listenfd);
				for(;;){
					if(Readline(accpectfd,buf,MAXLINE)==0)
						break;
					printf("recvied from tcp:%s\n",buf);
					Writen(accpectfd,buf,strlen(buf));
				}
				Close(accpectfd);
				exit(0);
			}
			Close(accpectfd);
		}
	}

	Close(listenfd);
	Close(udpfd);
	return 0;
}
