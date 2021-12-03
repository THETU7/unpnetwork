/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-23
  Version:0.1.0
*/

#include "../lib/help.h"

int main(int argc,char **argv){
	struct sockaddr_storage addr;
	int sockfd;

	if(argc<3){
		err_quit("usage: tcpserver1 <hostname/IPaddress> <service/port#>");
	}

	sockfd = Tcp_connect(argv[1], argv[2]);

	socklen_t len = sizeof(addr);
	getpeername(sockfd,(SA*)&addr,&len);
	printf("connect to %s\n",Sock_ntop_host((SA*)&addr,len));
	int n;
	char recvline[MAXLINE+1];
	/*
	 *while((n=Read(sockfd,recvline,MAXLINE))>0){
	 *    recvline[n]=0;
	 *    Fputs(recvline,stdout);
	 *}
	 */

	Writen(sockfd,"",1);
	n=Read(sockfd,recvline,MAXLINE);
	Fputs(recvline,stdout);
	exit(0);
}
