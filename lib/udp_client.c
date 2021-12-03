/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-24
  Version:0.1.0
*/

#include "help.h"

int udp_client(const char *host, const char *serv, SA **saptr, socklen_t *lenp){
	int fd, n;
	struct addrinfo hints,*res,*ressave;
	memset(&hints,0,sizeof(hints));
	hints.ai_socktype=SOCK_DGRAM;
	hints.ai_family=AF_UNSPEC;
	
	if((n=getaddrinfo(host,serv,&hints,&res))!=0){
		err_quit("udp_client error for %s, %s: %s",host, serv, gai_strerror(n));
	}

	ressave = res;

	do{
	fd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if(fd>=0)
		break;
	} while((res=res->ai_next)!=NULL);
	
	if(res==NULL)
		err_quit("udp_client error for %s, %s", host, serv);
	if(saptr){
		*saptr=(SA*)Malloc(res->ai_addrlen);
		memcpy((*saptr),res->ai_addr,res->ai_addrlen);
	}
	if(lenp)
		*lenp=res->ai_addrlen;
	
	return fd;
}

int Udp_client(const char *host, const char *serv, SA **saptr, socklen_t *lenp){
	return udp_client(host,serv,saptr,lenp);
}
