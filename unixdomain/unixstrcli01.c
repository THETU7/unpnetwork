/**********************************************************************
 * @ Copyright (C) 2021 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2021-11-15 00:01                                           *
 * @ File: unixstrcli01.c                                             *
 *                                                                    *
 * @ Description: unixdomain cli demo                                 *
 **********************************************************************/
#include "../lib/help.h"

int main(int argc, char **argv) {
  int sockfd;
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_LOCAL;
  strncpy(addr.sun_path, UNIXSTR_PATH, sizeof(addr.sun_path));

  sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

  Connect(sockfd, (SA *)&addr, sizeof(addr));

  void str_cil(int);
  str_cil(sockfd);
  return 0;
}
