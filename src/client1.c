/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-09
  Version:0.1.0
*/

#include "../lib/help.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main(){
	struct sockaddr_in cliScoket;
	void str_cil2(int);
	memset(&cliScoket, 0, sizeof(cliScoket));
	cliScoket.sin_family=AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&cliScoket.sin_addr);
	cliScoket.sin_port=htons(8080);
	int socketfd = Socket(AF_INET,SOCK_STREAM,0);
	Connect(socketfd, (SA*)&cliScoket, sizeof(cliScoket));
	str_cil2(socketfd);
	Close(socketfd);
	return 0;
}
