/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-09-29
  Version:0.1.0
*/
#ifndef HELP_H
#define HELP_H
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
//#include <file>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <poll.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef INFTIM
#define INFTIM (-1) /* infinite poll timeout */
#ifdef HAVE_POLL_H
#define INFTIM_UNPH /* tell unpxti.h we defined it */
#endif
#endif
#define MAXLINE 4096
#define SA struct sockaddr
#define LISTENQ 1024
#define UNIXSTR_PATH "/tmp/unix.str"

typedef void Sigfunc(int);

//初始化守护进程
int daemon_init(const char *pname, int facility);

char *sock_ntop(const SA *sockaddr, socklen_t addrlen);
int sock_bind_wild(int sockfd, int family);
int sock_cmp_addr(const SA *sockaddr1, const SA *sockaddr2, socklen_t addrlen);
char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen);
char *Sock_ntop_host(const struct sockaddr *sa, socklen_t salen);
// tcp
int tcp_connect(const char *host, const char *serv);
int tcp_listen(const char *host, const char *serv, socklen_t *addrlen);

// udp
int udp_client(const char *host, const char *serv, SA **saptr, socklen_t *lenp);
int udp_server(const char *host, const char *serv, socklen_t *addrlenp);
int udp_connect(const char *host, const char *serv);

// IO
ssize_t readn(int filedes, void *buf, size_t nbytes);
ssize_t written(int filedes, const void *buff, size_t nbytes);
ssize_t readline(int filedes, void *buff, size_t maxlen);
ssize_t readlinebuf(void **vptrptr);
ssize_t read_fd(int fd, void *ptr, size_t nbytes, int *recvfd);
ssize_t Read_fd(int fd, void *ptr, size_t nbytes, int *recvfd);
ssize_t write_fd(int fd, void *ptr, size_t nbytes, int sendfd);
ssize_t Write_fd(int fd, void *ptr, size_t nbytes, int sendfd);
// time
int readable_timeo(int fd, int sec);
int connect_timeo(int sockfd, const SA *saptr, socklen_t salen, int nesc);

//包裹函数
char *Sock_ntop(const struct sockaddr *sockaddr, socklen_t addrlen);
void Connect(int sockfd, const SA *servaddr, socklen_t addrlen);
void Bind(int sockfd, const SA *myaddr, socklen_t addrlen);
void Listen(int sockfd, int blocklog);
int Accept(int sockfd, SA *cliaddr, socklen_t *addrlen);
int Socket(int family, int type, int protocol);
void Writen(int fd, void *ptr, size_t nbytes);
ssize_t Readn(int filedes, void *buf, size_t nbytes);
ssize_t Readline(int filedes, void *buff, size_t nbytes);
char *Fgets(char *buf, int n, FILE *__stream);
void Fputs(const char *buf, FILE *__stream);
pid_t Fork();
void Close(int fd);
Sigfunc *Signal(int signo, Sigfunc *func);
void Dup2(int oldfd, int newfd);
int Select(int __nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
           struct timeval *timeout);
int Poll(struct pollfd *__fds, nfds_t __nfds, int __timeout);
ssize_t Sendto(int fd, void *buf, size_t n, int flags,
               const struct sockaddr *addr, socklen_t len);
ssize_t Recvfrom(int fd, void *buf, size_t n, int flags, SA *addr,
                 socklen_t *addr_len);
ssize_t Send(int fd, void *buf, size_t size, int flags);
ssize_t Recv(int fd, void *buf, size_t size, int flags);
void Getsockopt(int fd, int level, int optname, void *optval,
                socklen_t *optlen);
void Setsockopt(int fd, int level, int optname, const void *optval,
                socklen_t optlen);
int Tcp_connect(const char *host, const char *serv);
ssize_t Read(int fd, void *vptr, size_t n);
int Tcp_listen(const char *host, const char *serv, socklen_t *addrlen);
void *Malloc(size_t size);
int Udp_client(const char *host, const char *serv, SA **saptr, socklen_t *lenp);
int Udp_connect(const char *host, const char *serv);
int Udp_server(const char *host, const char *serv, socklen_t *addrlenp);
void Socketpair(int __domain, int __type, int __protocol, int *__fds);
void Waitpid(__pid_t __pid, int *__stat_loc, int __options);
void Shutdown(int fd, int how);
struct addrinfo *Host_serv(const char *host, const char *serv, int family,
                           int socktype);

char *gf_time();
//错误处理
void err_sys(const char *fmt, ...);
void err_quit(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_ret(const char *fmt, ...);
//信号处理
Sigfunc *signal(int signo, Sigfunc *func);

//阻塞设置
int Fcntl(int fd, int cmd, int arg);

int max(int a1, int a2);

#endif
