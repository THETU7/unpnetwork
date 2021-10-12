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
	for(;;){
		FD_SET(fileno(fp),&rest);
		FD_SET(sockfd,&rest);
		maxfdp1 = fileno(fp)>sockfd?fileno(fp)+1:sockfd+1;
		Select(maxfdp1,&rest,NULL,NULL,NULL);
		if(FD_ISSET(sockfd,&rest)){
			if(Readline(sockfd, recvline, MAXLINE)==0){
				exit(0);
			}
			Fputs(recvline,stdout);
		}

		if(FD_ISSET(fileno(fp),&rest)){
			if(Fgets(sendline,MAXLINE,stdin)==NULL)
				return;
			Writen(sockfd,sendline,strlen(sendline));
		}
	}
}
