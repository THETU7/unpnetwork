#include "help.h"

void Waitpid(__pid_t pid, int *stat, int options) {
  if (waitpid(pid, stat, options) == -1)
    err_sys("waitpid error");
}
