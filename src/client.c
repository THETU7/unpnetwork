/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-03
  Version:0.1.0
*/

#include "../lib/help.h"
#include <string.h>

void doit(int fd);
void doit2(int fd);

int main()
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(8080);
	int fd = Socket(AF_INET,SOCK_STREAM,0);
	Connect(fd,(SA*)&addr,sizeof(addr));
	doit2(fd);
	close(fd);
	return 0;
}

void doit(int fd){
	char buf[MAXLINE];
	if(readn(fd, buf, sizeof(buf))>0)
	{
		printf("%s",buf);
	}
}

void doit2(int fd){
	char buf[MAXLINE],recv[MAXLINE];
	while(fgets(buf, MAXLINE, stdin)!=NULL){
		Writen(fd,buf,sizeof(buf));
		Readn(fd, recv, sizeof(recv));
		fputs(recv, stdout);
	}
}
