/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-12
  Version:0.1.0
*/

#include "../lib/help.h"
#include <string.h>
#include <sys/select.h>

int main(int argc, char **argv){
	char buf[MAXLINE];
	char *addr, *port;
	socklen_t len;
	if(argc==2){
		port = argv[1];
	} else {
		port = "8080";
	}
	addr = "127.0.0.1";
	fd_set rset,allset;
	FD_ZERO(&rset);
	int clienfds[FD_SETSIZE];
	int maxfd=-1;
	int clientLen=0;
	memset(clienfds,-1,FD_SETSIZE);
	struct sockaddr_in saddr,caddr;
	memset(&saddr, 0, sizeof(saddr));
	inet_pton(AF_INET, addr, &saddr.sin_addr);
	saddr.sin_port=htons(atol(port));
	saddr.sin_family=AF_INET;
	int listenfd = Socket(AF_INET,SOCK_STREAM,0);
	Bind(listenfd,(SA*)&saddr,sizeof(saddr));
	Listen(listenfd,LISTENQ);
	FD_SET(listenfd,&rset);
	clienfds[0]=listenfd;
	maxfd=listenfd+1;
	clientLen++;
	int accectfd=-1;
	while(1){
		allset=rset;
		Select(maxfd,&allset,NULL,NULL,NULL);
		if(FD_ISSET(listenfd,&allset))
		{
			len = sizeof(caddr);
			accectfd = Accept(listenfd,(SA*)&caddr,&len);
			printf("connect from %s:%d\n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
			//fflush(stdout);
			FD_SET(accectfd,&rset);
			maxfd=maxfd>accectfd?maxfd:(accectfd+1);
			int i=0;
			for(i=0;i<FD_SETSIZE;++i){
				if(clienfds[i]<0){
					clienfds[i]=accectfd;
					clientLen++;
					break;
				}
			}
			if(i==FD_SETSIZE){
				printf("too many accectfd\n");
			}
		}
		int n;
		for(int i=1;i<clientLen;++i){
			if(clienfds[i]>=0){
				if(FD_ISSET(clienfds[i],&allset)){
					if((n=Readline(clienfds[i],buf,MAXLINE))==0){
						Close(clienfds[i]);
						FD_CLR(clienfds[i],&rset);
						printf("client %d closed\n",clienfds[i]);
						clienfds[i]=-1;
						continue;
					}
					printf("recive:%s",buf);
					Writen(clienfds[i],buf,n);
				}
			}
		}	
	}
	Close(listenfd);
	return 0;
}
