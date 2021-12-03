/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-19
  Version:0.1.0
*/

#include "../lib/help.h"

int main(){
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);
	addr.sin_port=htons(8080);
	addr.sin_family=AF_INET;
	int fd=Socket(AF_INET,SOCK_DGRAM,0);
	char buf[MAXLINE];
	for(;;){
		Fgets(buf,MAXLINE,stdin);
		Sendto(fd,buf,strlen(buf),0,(SA*)&addr,sizeof(addr));
		Recvfrom(fd,buf,MAXLINE,0,NULL,NULL);
		Fputs(buf,stdout);
	}
	Close(fd);
	return 0;
}
