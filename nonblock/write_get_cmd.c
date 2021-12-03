/**********************************************************************
 * @ Copyright (C) 2021 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2021-11-20 23:01                                           *
 * @ File: write_get_cmd.c                                            *
 *                                                                    *
 * @ Description: null                                                *
 **********************************************************************/

#include "web.h"

void write_get_cmd(struct file *fptr) {
  int n;
  char line[MAXLINE];

  n = snprintf(line, sizeof(line), GET_CMD, fptr->f_name);
  Writen(fptr->f_fd, line, n);
  printf("wrote %d bytes for %s\n", n, fptr->f_name);

  fptr->f_flags = F_READING;
  FD_SET(fptr->f_fd, &rset);
  maxfd = fptr->f_fd > maxfd ? fptr->f_fd : maxfd;
}
