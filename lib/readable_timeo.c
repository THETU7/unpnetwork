/**********************************************************************
 * @ Copyright (C) 2021 Zongyang All rights reserved.                 *
 *                                                                    *
 * @ Author: Zongyang                                                 *
 * @ Date: 2021-11-08 22:46                                           *
 * @ File: readable_timeo.c                                           *
 *                                                                    *
 * @ Description: check timeout with select                           *
 **********************************************************************/

#include "help.h"

int readable_timeo(int fd, int sec) {
  fd_set rest;
  struct timeval tv;

  FD_ZERO(&rest);
  FD_SET(fd, &rest);

  tv.tv_usec = 0;
  tv.tv_sec = sec;

  return select(fd + 1, &rest, NULL, NULL, &tv);
}
