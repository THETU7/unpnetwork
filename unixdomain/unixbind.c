/**********************************************************************
 * @ Copyright (C) 2021 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2021-11-14 22:49                                           *
 * @ File: unixbind.c                                                 *
 *                                                                    *
 * @ Description: a demo for unixdomain                               *
 **********************************************************************/

#include "../lib/help.h"

int main(int argc, char **argv) {
  struct sockaddr_un addr1, addr2;
  int sockfd;
  socklen_t len;

  if (argc != 2)
    err_quit("usage: unxibind <pathname>");
  memset(&addr1, 0, sizeof(addr1));
  unlink(argv[1]);
  strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path) - 1);
  addr1.sun_family = AF_LOCAL;
  sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);
  Bind(sockfd, (SA *)&addr1, sizeof(addr1));

  len = sizeof(addr2);

  if (getsockname(sockfd, (SA *)&addr2, &len) != 0)
    err_sys("getsockname error");
  printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);
  return 0;
}
