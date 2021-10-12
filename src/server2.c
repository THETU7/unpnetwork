/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-12
  Version:0.1.0
*/

#include "../lib/help.h"
#include <string.h>

int main(int argc, char **argv){
	char *addr, *port;
	socklen_t len;
	if(argc==2){
		port = argv[1];
	} else {
		port = "8080";
	}
	addr = "127.0.0.1";
	struct sockaddr_in saddr,caddr;
	memset(&saddr, 0, sizeof(saddr));
	inet_pton(AF_INET, addr, &saddr.sin_addr);
	saddr.sin_port=htons(atol(port));
	saddr.sin_family=AF_INET;
	int listenfd = Socket(AF_INET,SOCK_STREAM,0);
	Bind(listenfd,(SA*)&saddr,sizeof(saddr));
	Listen(listenfd,LISTENQ);

	while(1){
		len = sizeof(caddr);

		int accectfd = Accept(listenfd,(SA*)&caddr,&len);
		if(Fork()==0){
			Close(listenfd);
			Close(accectfd);
			exit(0);
		}
		Close(accectfd);
	}
	Close(listenfd);
}
