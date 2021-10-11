/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-09-29
  Version:0.1.0
*/

#include "help.h"
#include <string.h>

char *sock_ntop(const struct sockaddr *sa,socklen_t salen){
	char portstr[8];
	static char str[128];

	switch (sa->sa_family){
		case AF_INET:{
				struct sockaddr_in *sin = (struct sockaddr_in *)sa;
						
				if(inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str))==NULL)
					return NULL;
				if(ntohs(sin->sin_port)!=0){
					snprintf(portstr,sizeof(portstr), ":%d",ntohs(sin->sin_port));
					strcat(str,portstr);
				}

				return str;
			}
#ifdef IPV6 
		case AF_INET6:{
				struct sockaddr_in6 *sin = (struct sockaddr_in6 *)sa;
				
				str[0]='[';
				if(inet_ntop(AF_INET6, &sin->sin6_addr,str+1,sizeof(str-1))==NULL)
					return NULL;
				if(ntohs(sin->sin6_port)!=0){
					snprintf(portstr,sizeof(portstr), "]:%d",ntohs(sin->sin6_port));
					strcat(str,portstr);
				}
				return (str+1);		//没有端口
			}
#endif
	}
	return NULL;
}

char * Sock_ntop(const struct sockaddr *sa,socklen_t salen){
	char *ptr;
	if((ptr=sock_ntop(sa, salen))==NULL)
		err_sys("sock_ntop error");
	return ptr;
}



