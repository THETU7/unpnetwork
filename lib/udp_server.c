/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-24
  Version:0.1.0
*/

#include "help.h"
#include <netdb.h>

int udp_server(const char *host, const char *serv,socklen_t *addrlenp){
	int listenfd,n;
	struct addrinfo hints,*res,*ressave;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_DGRAM;
	hints.ai_flags=AI_PASSIVE;

	if((n=getaddrinfo(host,serv,&hints,&res))!=0)
		err_quit("udp_server error for %s, %s: %s", host, serv, gai_strerror(n));

	ressave = res;

	do {
		listenfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
		if(listenfd<0)
			continue;

		if(bind(listenfd,res->ai_addr,res->ai_addrlen)==0)
			break;

		Close(listenfd);
	}while ((res=res->ai_next)!=NULL);

	if(res==NULL)
		err_quit("udp_server error for %s, %s",host,serv);

//	Listen(listenfd,LISTENQ);

	if(addrlenp)
		addrlenp=res->ai_addrlen;

	freeaddrinfo(ressave);

	return listenfd;
}


int Udp_server(const char *host, const char *serv, socklen_t *addrlenp){
	return udp_server(host,serv,addrlenp);
}
