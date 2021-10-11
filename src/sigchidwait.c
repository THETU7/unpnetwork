/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-05
  Version:0.1.0
*/

#include "../lib/help.h"

void sigchld(int singo){
	pid_t pid;
	int sata;

	pid = wait(&sata);
	printf("child %d terminated\n",pid);
}
