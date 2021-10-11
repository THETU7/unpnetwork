/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-07
  Version:0.1.0
*/


#include "help.h"
#include <unistd.h>

char* Fgets(char *buf,int n,FILE* stream){
	char *get;
	if((get=fgets(buf,n,stream))==NULL&&ferror(stream))
		err_sys("fgets error");
	return get;
}

void Fputs(const char *restrict buf,FILE *restrict  _stream){
	if((fputs(buf, _stream))==EOF){
		err_sys("fputs error");
	}
}

void Dup2(int oldfd,int newfd){
	if(dup2(oldfd, newfd)<0)
		err_sys("dup2 error");
}
