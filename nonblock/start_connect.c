/**********************************************************************
 * @ Copyright (C) 2021 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2021-11-20 22:41                                           *
 * @ File: start_connect.c                                            *
 *                                                                    *
 * @ Description: start non-block connect                             *
 **********************************************************************/

#include "web.h"

void start_connect(struct file *fptr) {
  int fd, flags, n;
  struct addrinfo *ai;

  ai = Host_serv(fptr->f_host, SERV, 0, SOCK_STREAM);
  fd = Socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
  fptr->f_fd = fd;
  printf("start_connect for %s,fd %d\n", fptr->f_name, fd);
  flags = Fcntl(fd, F_GETFD, 0);
  Fcntl(fd, F_SETFD, flags | O_NONBLOCK);

  if ((n = connect(fd, ai->ai_addr, ai->ai_addrlen)) < 0) {
    if (errno != EINPROGRESS)
      err_sys("nonblocking connect error");
    fptr->f_flags = F_CONNECTING;
    FD_SET(fd, &rset);
    FD_SET(fd, &wset);
    if (fd > maxfd)
      fd = maxfd;
  } else if (n >= 0) {
    write_get_cmd(fptr);
  }
}
