/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-09-30
  Version:0.1.0
*/

#include "help.h"


ssize_t written(int fd,const void *vptr,size_t n){
	size_t nleft;
	ssize_t nwirtten;
	const char *ptr=vptr;
	nleft = n;
	while(nleft>0){
		if((nwirtten=write(fd,ptr,nleft))<=0){
			if(nwirtten<0 && errno==EINTR)
				nwirtten = 0;
			else 
				return -1;
		}
		nleft -=nwirtten;
		ptr+=nwirtten;
	}
	return n;
}

void Writen(int fd, void *ptr, size_t nbytes){
	if (written(fd, ptr, nbytes) != nbytes)
		err_sys("writen error");
}
