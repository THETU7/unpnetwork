/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-10-02
  Version:0.1.0
*/

#include "help.h"
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

int Socket(int family, int type, int protocol) {
  int fd;
  if ((fd = socket(family, type, protocol)) < 0)
    err_sys("Socket error");
  return fd;
}

void Connect(int sockfd, const SA *servaddr, socklen_t addrlen) {
  if (connect(sockfd, servaddr, addrlen) < 0) {
    err_sys("Connect error");
  }
}

void Bind(int sockfd, const SA *myaddr, socklen_t addrlen) {
  if (bind(sockfd, myaddr, addrlen) < 0)
    err_sys("Bind error");
}

void Listen(int sockfd, int blocklog) {
  if (listen(sockfd, blocklog) < 0)
    err_sys("Listen error");
}

int Accept(int sockfd, SA *cliaddr, socklen_t *addrlen) {
  int fd;
again:
  if ((fd = accept(sockfd, cliaddr, addrlen)) < 0) {
#ifdef EPROTO
    if (errno == EPROTO || errno == ECONNABORTED)
#else
    if (errno == ECONNABORTED)
#endif
      goto again;
    else
      err_sys("Accept error");
  }
  return fd;
}

pid_t Fork() {
  pid_t pid;
  if ((pid = fork()) < 0)
    err_sys("Fork error");
  return pid;
}

void Close(int fd) {
  if (close(fd) < 0) {
    err_sys("Close error");
  }
}

ssize_t Sendto(int fd, void *buf, size_t n, int flags,
               const struct sockaddr *addr, socklen_t len) {
  ssize_t nsend = -1;
  if ((nsend = sendto(fd, buf, n, flags, addr, len)) < 0) {
    err_sys("sendto error");
  }
  return nsend;
}

ssize_t Recvfrom(int fd, void *buf, size_t n, int flags, SA *addr,
                 socklen_t *addr_len) {
  int nread = -1;
  if ((nread = recvfrom(fd, buf, n, flags, addr, addr_len)) < 0) {
    err_sys("recvfrom error");
  }
  return nread;
}

ssize_t Send(int fd, void *buf, size_t size, int flags) {
  int nsend = -1;
  if ((nsend = send(fd, buf, size, flags)) < 0) {
    err_sys("send error");
  }
  return nsend;
}

ssize_t Recv(int fd, void *buf, size_t size, int flags) {
  int nread = -1;
  if ((nread = recv(fd, buf, size, flags)) < 0) {
    err_sys("recv error");
  }
  return nread;
}

void Setsockopt(int fd, int level, int optname, const void *optval,
                socklen_t optlen) {
  if (setsockopt(fd, level, optname, optval, optlen) < 0)
    err_sys("setsockopt error");
}

void Getsockopt(int fd, int level, int optname, void *optval,
                socklen_t *optlen) {
  if (getsockopt(fd, level, optname, optval, optlen) < 0)
    err_sys("getsockopt error");
}

void Socketpair(int __domain, int __type, int __protocol, int *__fds) {
  if (socketpair(__domain, __type, __protocol, __fds) == -1)
    err_sys("socketpair error");
}

void Shutdown(int fd, int how) {
  if (shutdown(fd, how) < 0)
    err_sys("shutdown error");
}
