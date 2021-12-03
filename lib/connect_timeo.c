/**********************************************************************
 * @ Copyright (C) 2021 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2021-11-07 23:13                                           *
 *                                                                    *
 **********************************************************************/

#include "help.h"
#include <sys/socket.h>

static void connect_alarm(int);

int connect_timeo(int sockfd, const SA *saptr, socklen_t salen, int nesc) {
  Sigfunc *sigfunc;
  int n;

  sigfunc = Signal(SIGALRM, connect_alarm);
  if (alarm(nesc) != 0)
    err_msg("connect_timeo: alarm was already set");

  if ((n = connect(sockfd, saptr, salen)) < 0) {
    close(sockfd);
    if (errno == EINTR)
      errno = ETIMEDOUT;
  }
  alarm(0);
  Signal(SIGALRM, sigfunc);

  return n;
}

static void connect_alarm(int signo) { return; }
