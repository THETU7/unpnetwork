/**********************************************************************
 * @ Copyright (C) 2021 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2021-11-17 22:10                                           *
 * @ File: mycat.c                                                    *
 *                                                                    *
 * @ Description: transfer description in the process                 *
 **********************************************************************/

#include "../lib/help.h"

int my_open(const char *, int);

int main(int argc, char **argv) {
  if (argc != 2) {
    err_quit("usage: mycat <pathname>");
  }

  int fd, n;
  char buff[MAXLINE];

  if ((fd = my_open(argv[1], O_RDONLY)) < 0) {
    err_sys("cannot open %s", argv[1]);
  }

  while ((n = Read(fd, buff, MAXLINE)) > 0)
    Writen(STDOUT_FILENO, buff, n);

  return 0;
}
