/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-05
  Version:0.1.0
*/

#include "../lib/help.h"

/*
 *	//由于Unix的信号排队机制导致，多个信号同时处理的问题
 *	//wait函数不能保证在子进程未终结时是否阻塞，所以只能同时处理一个信号
 *void sigchld(int singo){
 *    pid_t pid;
 *    int sata;
 *
 *    pid = wait(&sata);
 *    printf("child %d terminated\n",pid);
 *}
 */


void sigchld(int singo){
	pid_t pid;
	int stat;

	while((pid=waitpid(-1,&stat,WNOHANG))>0){
		printf("child %d terminated\n",pid);
	}
}
