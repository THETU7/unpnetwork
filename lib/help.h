/*
  The BSD License(BSD)

  Copyright (c) 2021 Zongyang
  Author:Zongyang
  Date:2021-09-29
  Version:0.1.0
*/
#ifndef HELP_H
#define HELP_H
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
//#include <file>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define MAXLINE 4096
#define SA struct sockaddr
#define LISTENQ 1024

typedef void Sigfunc(int);

char *sock_ntop(const SA *sockaddr, socklen_t addrlen);
int sock_bind_wild(int sockfd,int family);
int sock_cmp_addr(const SA *sockaddr1,const SA *sockaddr2,socklen_t addrlen);

//IO
ssize_t readn(int filedes,void *buf,size_t nbytes);
ssize_t written(int filedes,const void *buff,size_t nbytes);
ssize_t readline(int filedes,void *buff,size_t maxlen);
ssize_t readlinebuf(void **vptrptr);

//包裹函数
char *Sock_ntop(const struct sockaddr *sockaddr, socklen_t addrlen);
void Connect(int sockfd, const SA *servaddr, socklen_t addrlen);
void Bind(int sockfd, const SA *myaddr, socklen_t addrlen);
void Listen(int sockfd, int blocklog);
int Accept(int sockfd, SA *cliaddr, socklen_t *addrlen);
int Socket(int family, int type, int protocol);
void Writen(int fd, void *ptr, size_t nbytes);
ssize_t Readn(int filedes,void *buf,size_t nbytes);
ssize_t Readline(int filedes,void *buff,size_t nbytes);
char* Fgets(char *buf,int n,FILE *__stream);
void Fputs(const char *buf,FILE *__stream);
pid_t Fork();
void Close(int fd);
Sigfunc * Signal(int signo, Sigfunc *func);
void Dup2(int oldfd,int newfd);
//错误处理
void err_sys(const char* fmt, ...);

//信号处理
Sigfunc *signal(int signo, Sigfunc *func);

#endif
