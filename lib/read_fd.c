/**********************************************************************
 * @ Copyright (C) 2021 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2021-11-17 23:56                                           *
 * @ File: read_fd.c                                                  *
 *                                                                    *
 * @ Description: NULL                                                *
 **********************************************************************/

#include "help.h"
#include <asm-generic/socket.h>

#define HAVE_MSGHDR_MSG_CONTROL

ssize_t read_fd(int fd, void *ptr, size_t nbytes, int *recvfd) {
  struct msghdr msg;
  struct iovec iov[1];
  ssize_t n;

#ifdef HAVE_MSGHDR_MSG_CONTROL
  union {
    struct cmsghdr cm;
    char control[CMSG_SPACE(sizeof(int))];
  } control_un;

  struct cmsghdr *cmptr;

  msg.msg_control = control_un.control;
  msg.msg_controllen = sizeof(control_un.control);
#else
  int newfd;
  msg.msg_accrights = (caddr_t)&newfd;
  msg.msg_accrightslen = sizeof(int);
#endif

  msg.msg_name = NULL;
  msg.msg_namelen = 0;

  iov[0].iov_base = ptr;
  iov[0].iov_len = nbytes;
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;

  if ((n = recvmsg(fd, &msg, 0)) <= 0)
    return n;

#ifdef HAVE_MSGHDR_MSG_CONTROL
  if ((cmptr = CMSG_FIRSTHDR(&msg)) != NULL &&
      cmptr->cmsg_len == CMSG_LEN(sizeof(int))) {
    if (cmptr->cmsg_level != SOL_SOCKET)
      err_quit("control level != SOL_SOCKET");
    if (cmptr->cmsg_type != SCM_RIGHTS)
      err_quit("control type != SCM_RIGHTS");

    *recvfd = *((int *)CMSG_DATA(cmptr));
  } else
    *recvfd = -1;
#else
  if (msg.msg_accrightslen == sizeof(int))
    *recvfd = newfd;
  else
    *recvfd = -1;
#endif

  return n;
}

ssize_t Read_fd(int fd, void *ptr, size_t nbytes, int *recvfd) {
  ssize_t n;

  if ((n = read_fd(fd, ptr, nbytes, recvfd)) < 0)
    err_sys("read_fd error");

  return (n);
}
