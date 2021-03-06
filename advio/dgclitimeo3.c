/**********************************************************************
 * @ Copyright (C) 2021 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2021-11-11 23:54                                           *
 * @ File: dgclitimeo3.c                                              *
 *                                                                    *
 * @ Description: set timeout check for recvfrom                      *
 **********************************************************************/

#include "../lib/help.h"

static void sig_alrm(int);

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen) {
  int n;
  char sendline[MAXLINE], recvline[MAXLINE + 1];

  Signal(SIGALRM, sig_alrm);

  while (Fgets(sendline, MAXLINE, fp) != NULL) {
    Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

    alarm(5);

    if ((n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0) {
      if (errno == EINTR)
        fprintf(stderr, "socket timeout\n");
      else
        err_sys("recvfrom error");
    } else {
      alarm(0);
      recvline[n] = 0;
      Fputs(recvline, stdout);
    }
  }
}

static void sig_alrm(int signo) { return; }
