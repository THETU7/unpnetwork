/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-02
  Version:0.1.0
*/


#include "../lib/help.h"
#include <time.h>
#include <string.h>

void doit(int fd);
void doit2(int fd);
void sigchld(int signo);

int main()
{
	struct sockaddr_in sockaddr, cliaddr;
	socklen_t len;
	char buf[MAXLINE];
	void sigchld(int);
	int listenfd = Socket(AF_INET,SOCK_STREAM,0);
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family=AF_INET;
	sockaddr.sin_addr.s_addr=htonl(INADDR_ANY);//l -> long
	sockaddr.sin_port=htons(8080);//s -> short
	Bind(listenfd,(SA*)&sockaddr,sizeof(sockaddr));
	Listen(listenfd, LISTENQ);
	Signal(SIGCLD, sigchld);
	while(1){
		len = sizeof(cliaddr);
		int clientfd=Accept(listenfd, (SA*)&cliaddr, &len);
		printf("Connect from %s ,port %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, buf, sizeof(buf)),ntohs(cliaddr.sin_port));
		if(Fork()==0){
			Close(listenfd);
			doit2(clientfd);
			Close(clientfd);
			exit(0);
		}
		Close(clientfd);
}
	Close(listenfd);
	return 0;
}

void doit(int fd)
{
	time_t tirck;
	char buf[MAXLINE];
	tirck = time(NULL);
	snprintf(buf,sizeof(buf),"%.24s\r\n", ctime(&tirck));
	Writen(fd, buf, strlen(buf));
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

/*
 *void sigchld(int signo){
 *    pid_t pid;
 *    int stat;
 *    
 *    while((pid = waitpid(-1,&stat,WNOHANG))>0)
 *        printf("child %d terminated\n",pid);
 *}
 */
