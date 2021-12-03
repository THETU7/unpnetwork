/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-24
  Version:0.1.0
*/

#include "../lib/help.h"
#include <time.h>

int main(int argc, char **argv){

	int listenfd=-1;
	if(argc==2){
		listenfd=Udp_server(NULL,argv[1],NULL);
	} else if(argc==3){
		listenfd=Udp_server(argv[1],argv[2],NULL);
	} else{
		err_quit("usage: daytimeupd [<hostname>] <service or port#>");
	}

	struct sockaddr_storage ss;
	char buf[MAXLINE],sendbuf[MAXLINE];
	for(;;){
		socklen_t len = sizeof(ss);
		
		Recvfrom(listenfd,buf,MAXLINE,0,(SA*)&ss,&len);

		time_t ticks = time(NULL);
		snprintf(sendbuf,MAXLINE,"%.24s\n",ctime(&ticks));
		Sendto(listenfd,sendbuf,strlen(sendbuf),0,(SA*)&ss,sizeof(ss));
	}

}
