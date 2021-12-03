/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-23
  Version:0.1.0
*/

#include "help.h"
#include <netdb.h>

int tcp_listen(const char *host, const char *service, socklen_t *addrlenp){
   /* int				listenfd, n;*/
	/*const int		on = 1;*/
	/*struct addrinfo	hints, *res, *ressave;*/

	/*bzero(&hints, sizeof(struct addrinfo));*/
	/*hints.ai_flags = AI_PASSIVE;*/
	/*hints.ai_family = AF_UNSPEC;*/
	/*hints.ai_socktype = SOCK_STREAM;*/
	/*if ( (n = getaddrinfo(host, service, &hints, &res)) != 0)*/
		/*err_quit("tcp_listen error for %s, %s: %s",*/
				 /*host, service, gai_strerror(n));*/

	struct addrinfo hints,*res,*ressave;
	memset(&hints,0,sizeof(hints));
	//hins.ai_flags=AI_PASSIVE;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	int listenfd,n;
	const int on=1;
	if((n=getaddrinfo(host,service,&hints,&res))!=0){
		err_quit("tcp_listen error for %s, %s,: %s",host, service, gai_strerror(n));
	}
	ressave = res;
	do {
		listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(listenfd<0)
			continue;

		Setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
		if(bind(listenfd,res->ai_addr,res->ai_addrlen)==0)
			break;

		Close(listenfd);
	}while ((res=res->ai_next)!=NULL);
	
	if(res == NULL)
		err_sys("tcp_listen error for %s, %s",host,service);

	Listen(listenfd,LISTENQ);

	if(addrlenp){
		*addrlenp = res->ai_addrlen;
	}

	freeaddrinfo(ressave);

	return listenfd;
}


int Tcp_listen(const char *host, const char *service, socklen_t *addrlenp){
	return tcp_listen(host,service,addrlenp);
}

