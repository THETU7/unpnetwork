/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-07
  Version:0.1.0
*/

#include "../lib/help.h"
#include <stdio.h>
#include <string.h>
#include "sum.h"
void str_echo(int fd){
	long arg1,arg2;
	char buf[MAXLINE];
	ssize_t n;
	for(;;){
		if((n=readn(fd,buf,MAXLINE))==0)
			return;
		if(sscanf(buf, "%ld,%ld", &arg1,&arg2)==2){
			snprintf(buf,sizeof(buf),"%ld\n",arg1+arg2);
		} 
		else {
			snprintf(buf,sizeof(buf),"input error\n");
		}
		Writen(fd,buf,sizeof(buf));
	}
}

void str_echo2(int fd){
	struct sum s1;
	struct result re;
	ssize_t n;
	for(;;){
		if((n=Readn(fd,(void*)&s1,sizeof(s1)))==0)
			return;
		printf("arg1=%ld,arg2=%ld\n",s1.arg1,s1.arg2);
		re.sum=s1.arg1+s1.arg2;
		printf("sum=%ld\n",re.sum);
		Writen(fd,(void*)&re,sizeof(re));
	}
}
