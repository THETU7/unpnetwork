/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-24
  Version:0.1.0
*/

#include "../lib/help.h"

int main(int argc,char **argv){
	if(argc !=3){
		printf("usage: daytime1 <hostname/IPaddress> <service/port#>\n");
		exit(-1);
	}

	int sockfd;
	char buf[MAXLINE];
	struct sockaddr_storage *ss;
	socklen_t len;

	sockfd = Udp_client(argv[1],argv[2],(SA**)&ss,&len);
	printf("Sending to %s\n",Sock_ntop_host((SA*)ss,len));

	Sendto(sockfd,"",1,0,(SA*)ss,len);

	int n= Recvfrom(sockfd,buf,MAXLINE,0,(SA*)ss,&len);
	buf[n]='\0';
	Fputs(buf,stdout);
	free(ss);
	Close(sockfd);
	return 0;
}
