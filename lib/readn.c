/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-09-30
  Version:0.1.0
*/

#include "help.h"
ssize_t readn(int fd,void *vptr,size_t n)
{
	size_t nleft;
	ssize_t nread;
	char *ptr=vptr;
	nleft=n;
	while(nleft>0){
		if((nread=read(fd,ptr,nleft))<0){
			if(errno==EINTR)
				nread=0;
			else 
				return -1;
		} else if (nread==0)
			break;
		nleft-=nread;
		ptr+=nread;
	}
	return (n-nleft);
}

ssize_t Readn(int fd,void *vptr,size_t n)
{
	ssize_t nread;
	if((nread=readn(fd,vptr,n))<0)
		err_sys("Readn error!");
	return nread;
}

ssize_t Read(int fd,void *vptr,size_t n){
	int nread;
	if((nread=read(fd,vptr,n))<0){
		if(errno==EINTR)
			nread=0;
		else 
			err_sys("read error");
	}
	return nread;
}
