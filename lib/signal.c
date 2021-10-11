/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-05
  Version:0.1.0
*/

#include "help.h"

Sigfunc* signal(int signo, Sigfunc *func){
	struct sigaction act,oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	if(signo == SIGALRM){
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	} else {
#ifdef SA_RESTART 
		act.sa_flags |=SA_RESTART;
#endif
	}
	if(sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return (oact.sa_handler);
}

Sigfunc * Signal(int signo, Sigfunc *func){
	Sigfunc *sigfunc;

	if ((sigfunc=signal(signo, func))==SIG_ERR)
		err_sys("signal error");
	return sigfunc;
}
