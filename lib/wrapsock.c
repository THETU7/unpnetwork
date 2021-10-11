/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-02
  Version:0.1.0
*/

#include "help.h"
#include <sys/socket.h>

int Socket(int family, int type, int protocol){
	int fd;
	if((fd=socket(family,type,protocol))<0)
		err_sys("Socket error");
	return fd;
}

void Connect(int sockfd, const SA *servaddr, socklen_t addrlen){
	if(connect(sockfd,servaddr,addrlen)<0){
		err_sys("Connect error");
	}
}

void Bind(int sockfd, const SA *myaddr, socklen_t addrlen){
	if(bind(sockfd,myaddr,addrlen)<0)
		err_sys("Bind error");
}

void Listen(int sockfd, int blocklog){
	if(listen(sockfd, blocklog)<0)
		err_sys("Listen error");
}


int Accept(int sockfd, SA *cliaddr, socklen_t *addrlen){
	int fd;
again:
	if((fd=accept(sockfd, cliaddr, addrlen))<0){
#ifdef	EPROTO 
		if (errno==EPROTO||errno==ECONNABORTED)
#else
		if (errno==ECONNABORTED)
#endif
			goto again;
		else
			err_sys("Accept error");
	}
	return fd;
}

pid_t Fork(){
	pid_t pid;
	if((pid=fork())<0)
		err_sys("Fork error");
	return pid;
}

void Close(int fd){
	if(close(fd)<0){
		err_sys("Close error");
	}
}
