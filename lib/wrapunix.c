#include "help.h"

int Fcntl(int fd, int cmd, int arg) {
  int n;

  if ((n = fcntl(fd, cmd, arg)) < 0) {
    err_sys("fcntl error");
  }
  return n;
}
