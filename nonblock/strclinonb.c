/**********************************************************************
 * @ Copyright (C) 2021 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2021-11-20 18:49                                           *
 * @ File: strclinonb.c                                               *
 *                                                                    *
 * @ Description: non-block client                                    *
 **********************************************************************/

#include "../lib/help.h"
#include <asm-generic/errno.h>
#include <unistd.h>

void str_cil(FILE *fp, int sockfd) {
  int maxfd, val, stdineof;
  ssize_t n, nwritten;
  fd_set wset, rset;
  char to[MAXLINE], from[MAXLINE];
  char *tooptr, *toiptr, *froptr, *friptr;

  val = Fcntl(sockfd, F_GETFL, 0);
  //设置为非阻塞
  Fcntl(sockfd, F_SETFL, val | O_NONBLOCK);
  val = Fcntl(STDIN_FILENO, F_GETFL, 0);
  //设置为非阻塞
  Fcntl(STDIN_FILENO, F_SETFL, val | O_NONBLOCK);
  val = Fcntl(STDOUT_FILENO, F_GETFL, 0);
  //设置为非阻塞
  Fcntl(STDOUT_FILENO, F_SETFL, val | O_NONBLOCK);

  tooptr = toiptr = to;
  froptr = friptr = from;
  maxfd = max(max(STDIN_FILENO, STDOUT_FILENO), sockfd);
  stdineof = 0;

  for (;;) {
    FD_ZERO(&wset);
    FD_ZERO(&rset);
    if (stdineof == 0 && toiptr < &to[MAXLINE])
      FD_SET(STDIN_FILENO, &rset);
    if (friptr < &from[MAXLINE])
      FD_SET(sockfd, &rset);
    if (tooptr != toiptr)
      FD_SET(sockfd, &wset);
    if (froptr != friptr)
      FD_SET(STDOUT_FILENO, &wset);

    Select(maxfd + 1, &rset, &wset, NULL, NULL);

    if (FD_ISSET(STDIN_FILENO, &rset)) {
      if ((n = read(STDIN_FILENO, toiptr, &to[MAXLINE] - toiptr)) < 0) {
        if (errno != EWOULDBLOCK)
          err_sys("read error on stdin");
      } else if (n == 0) {
        fprintf(stderr, "%s: EOF on stdin\n", gf_time());
        stdineof = 1;
        if (tooptr == toiptr)
          Shutdown(sockfd, SHUT_WR);
      } else {
        fprintf(stderr, "%s: read %d bytes from stdin\n", gf_time(), (int)n);
        toiptr += n;
        FD_SET(sockfd, &wset);
      }
    }

    if (FD_ISSET(sockfd, &rset)) {
      if ((n = read(sockfd, from, &from[MAXLINE] - friptr)) < 0) {
        if (errno != EWOULDBLOCK)
          err_sys("read error on socket");
      } else if (n == 0) {
        fprintf(stderr, "%s: EOF on socket", gf_time());
        if (stdineof)
          return;
        else
          err_quit("str_cil: server terminated prematurely");
      } else {
        fprintf(stderr, "%s: read %d bytes from socket", gf_time(), (int)n);
        friptr += n;
        FD_SET(STDOUT_FILENO, &wset);
      }
    }

    if (FD_ISSET(sockfd, &wset) && (n = toiptr - tooptr) > 0) {
      if ((nwritten = write(sockfd, tooptr, n)) < 0) {
        if (errno != EWOULDBLOCK)
          err_sys("write error on sockfd");
      } else {
        fprintf(stderr, "%s: wrote %d bytes to socket\n", gf_time(),
                (int)nwritten);
        tooptr += nwritten;
        if (tooptr == toiptr) {
          tooptr = toiptr = to;
          if (stdineof)
            Shutdown(sockfd, SHUT_WR);
        }
      }
    }

    if (FD_ISSET(STDOUT_FILENO, &wset) && (n = friptr - froptr) > 0) {
      if ((nwritten = write(STDOUT_FILENO, friptr, n)) < 0) {
        if (errno != EWOULDBLOCK) {
          err_sys("write error on stdout");
        }
      } else {
        fprintf(stderr, "%s: wrote %d bytes to stdout\n", gf_time(),
                (int)nwritten);
        froptr += nwritten;
        if (froptr == friptr) {
          froptr = friptr = from;
        }
      }
    }
  }
}
