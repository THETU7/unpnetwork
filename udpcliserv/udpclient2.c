/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-19
  Version:0.1.0
*/

#include "../lib/help.h"

int main(){
	char buf[MAXLINE];
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);
	addr.sin_port=htons(8080);
	addr.sin_family=AF_INET;
	
	fd_set sets;
	FD_ZERO(&sets);
	int fd=Socket(AF_INET,SOCK_DGRAM,0);
	Connect(fd, (SA*)&addr, sizeof(addr));
	int maxfd1=fd>STDIN_FILENO?fd:STDIN_FILENO;
	
	for(;;){
		FD_SET(fd,&sets);
		FD_SET(STDIN_FILENO,&sets);
		Select(maxfd1+1,&sets,NULL,NULL,NULL);
		if(FD_ISSET(fd,&sets)){
			Recv(fd,buf,MAXLINE,0);
			Fputs(buf,stdout);
			memset(buf,0,sizeof(buf));
		}
		if(FD_ISSET(STDIN_FILENO,&sets)){
			Fgets(buf,MAXLINE,stdin);
			Send(fd,buf,strlen(buf),0);
		}
	}
	Close(fd);
}
