/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-12
  Version:0.1.0
*/

#include "../lib/help.h"
#include <stdio.h>
#include <sys/select.h>

void str_cil(FILE *fp,int sockfd){
	int maxfdp1;
	fd_set rest;
	FD_ZERO(&rest);
	char sendline[MAXLINE],recvline[MAXLINE];
	int filefd=fileno(fp);
	int stdinof=0;
	for(;;){
		if(stdinof==0)
			FD_SET(filefd,&rest);
		FD_SET(sockfd,&rest);
		maxfdp1 = filefd>sockfd?filefd+1:sockfd+1;
		Select(maxfdp1,&rest,NULL,NULL,NULL);
		if(FD_ISSET(sockfd,&rest)){
			if(Readline(sockfd, recvline, MAXLINE)==0){
				if(stdinof==1)
					return;
				else 
					err_quit("str_cli: server terminated prematurely");
			}
			Fputs(recvline,stdout);
		}

		if(FD_ISSET(filefd,&rest)){
			if(Readline(filefd,sendline,MAXLINE)==0){
				shutdown(sockfd, SHUT_WR);	
				stdinof=1;
				FD_CLR(filefd,&rest);
				continue;
			}
			Writen(sockfd,sendline,strlen(sendline));
		}
	}
}
