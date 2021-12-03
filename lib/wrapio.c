/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-15
  Version:0.1.0
*/


#include "help.h"

int Select(int __nfds, fd_set *restrict __readfds, fd_set *restrict __writefds, fd_set *restrict __exceptfds, struct timeval *restrict __timeout){
	int n=0;
	if((n=select(__nfds,__readfds,__writefds,__exceptfds,__timeout))<0)
		err_sys("select error");
	return n;
}

int Poll(struct pollfd *__fds, nfds_t __nfds, int __timeout){
	int n;
	if((n=poll(__fds,__nfds,__timeout))<0){
		err_sys("poll error");
	}
	else if(n==0){
		err_quit("poll timeout");
	}
	return n;
}


