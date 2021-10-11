/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-07
  Version:0.1.0
*/

#include "../lib/help.h"
/*#include <arpa/inet.h>*/
/*#include <netinet/in.h>*/
void doit2(int);
void str_echo2(int);

int main(){
	struct sockaddr_in s_socket,c_socket;
	socklen_t len;
	int clientfd;
	void sigchld(int);
	memset(&s_socket,0,sizeof(s_socket));
	s_socket.sin_family=AF_INET;
	s_socket.sin_addr.s_addr=htonl(INADDR_ANY);
	s_socket.sin_port=htons(8080);
	int listenfd= Socket(AF_INET,SOCK_STREAM,0);
	Bind(listenfd,(SA*)&s_socket,sizeof(s_socket));	
	Listen(listenfd,LISTENQ);
	Signal(SIGCHLD,sigchld);
	while(1){
		len = sizeof(c_socket);
		clientfd=Accept(listenfd,(SA*)&c_socket,&len);
		printf("Connect from %s : %d\n",inet_ntoa(c_socket.sin_addr),ntohs(c_socket.sin_port));
		if(Fork()==0){
			Close(listenfd);
			str_echo2(clientfd);
			Close(clientfd);
			printf("quit\n");
			exit(0);
		}
		Close(clientfd);
	}
	Close(listenfd);
	return 0;
}

void doit2(int fd){
	char buf[MAXLINE];
	ssize_t nread;
again:
	while((nread=read(fd,buf,sizeof(buf)))>0){
		Writen(fd,buf,sizeof(buf));
	}

	if(nread<0&&errno==EINTR){
		goto again;
	} else if(nread<0) {
		err_sys("read error");
	}
}

