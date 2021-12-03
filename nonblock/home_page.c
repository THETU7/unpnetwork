/**********************************************************************
 * @ Copyright (C) 2021 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2021-11-20 22:29                                           *
 * @ File: home_page.c                                                *
 *                                                                    *
 * @ Description: get home page of host                               *
 **********************************************************************/

#include "web.h"

void home_page(const char *host, const char *fname) {
  int fd, n;
  char line[MAXLINE];
  fd = Tcp_connect(host, SERV);

  n = snprintf(line, sizeof(line), GET_CMD, fname);
  Writen(fd, line, n);
  for (;;) {
    if ((n = Read(fd, line, MAXLINE)) == 0)
      break;
    printf("read %d bytes of home page\n", n);
  }
  printf("end-fo-file on home page\n");
  Close(fd);
}
