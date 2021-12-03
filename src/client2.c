/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-12
  Version:0.1.0
*/

#include "../lib/help.h"
#include <string.h>

int main(int argc,char **argv){
	char *addr="127.0.0.1";
	char *port="8080";
	void str_cil(FILE*,int fd);
	if(argc>2){
		addr=argv[1];
		port=argv[2];
	}
	else if(argc>1){
		err_sys("fomat:<addr:port>\n");
	}

	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	inet_pton(AF_INET,addr,&saddr.sin_addr);
	saddr.sin_port=htons(atoi(port));
	saddr.sin_family=AF_INET;
	int fd = Socket(AF_INET,SOCK_STREAM,0);
	Connect(fd,(SA*)&saddr,sizeof(saddr));
	str_cil(stdin,fd);
	Close(fd);
	return 0;
}
