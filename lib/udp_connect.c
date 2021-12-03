/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-24
  Version:0.1.0
*/

#include  "help.h"
#include <netdb.h>

int udp_connect(const char* host, const char *serv){
	int sockfd,n;
	struct addrinfo hints,*res,*ressave;

	memset(&hints,0,sizeof(hints));
	hints.ai_socktype=SOCK_DGRAM;
	hints.ai_family=AF_UNSPEC;

	if((n=getaddrinfo(host,serv,&hints,&res))!=0){
		err_quit("udp_connect error %s, %s: %s", host, serv, gai_strerror(n));
	}

	ressave = res;

	do {
		sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
		if(sockfd<0)
			continue;
		
		if(connect(sockfd,res->ai_addr,res->ai_addrlen)==0)
			break;

		Close(sockfd);

	} while((res=res->ai_next) !=NULL);
	
	if(res==NULL)
		err_quit("udp_connect error %s, %s",host, serv);

	freeaddrinfo(ressave);

	return sockfd;
}

int Udp_connect(const char *host, const char *serv){
	return udp_connect(host,serv);
}
