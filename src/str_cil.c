/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-07
  Version:0.1.0
*/

#include "../lib/help.h"
#include "sum.h"

void str_cil(int fd) {
  char buf[MAXLINE], recv[MAXLINE];
  while (Fgets(buf, MAXLINE, stdin) != NULL) {
    Writen(fd, buf, sizeof(buf));
    if (Readn(fd, recv, MAXLINE) == 0) {
      printf("str_cli: server terminated prematurely\n");
      exit(0);
    }
    Fputs(recv, stdout);
  }
}

void str_cil2(int fd) {
  char buf[MAXLINE];
  struct sum s1;
  struct result se;
  while (Fgets(buf, MAXLINE, stdin) != NULL) {
    if (sscanf(buf, "%ld,%ld", &s1.arg1, &s1.arg2) != 2) {
      printf("invail input\n");
      continue;
    }
    Writen(fd, (void*)&s1, sizeof(s1));
    if (Readn(fd, (void*)&se, sizeof(se)) == 0) {
      printf("str_cli: server terminated prematurely\n");
      exit(0);
    }
    printf("s1.arg1=%ld,s1.arg2=%ld\n", s1.arg1, s1.arg2);
    printf("%ld\n", se.sum);
    se.sum = 0;
  }
}
