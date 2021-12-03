#include "../lib/help.h"

int main(int argc, char **argv) {
  struct sockaddr_un saddr, caddr;
  void sigchld(int);
  void str_echo(int);
  memset(&saddr, 0, sizeof(saddr));
  unlink(UNIXSTR_PATH);
  saddr.sun_family = AF_LOCAL;
  stpncpy(saddr.sun_path, UNIXSTR_PATH, sizeof(saddr.sun_path));
  int listenfd = Socket(AF_LOCAL, SOCK_STREAM, 0);
  Bind(listenfd, (SA *)&saddr, sizeof(saddr));
  Listen(listenfd, LISTENQ);
  Signal(SIGCHLD, sigchld);

  socklen_t clilen;
  int connfd;
  pid_t childpid;
  for (;;) {
    clilen = sizeof(caddr);
    if ((connfd = accept(listenfd, (SA *)&caddr, &clilen)) < 0) {
      if (errno == EINTR)
        continue;
      else
        err_sys("accpect error");
    }
    if ((childpid = Fork()) == 0) {
      Close(listenfd);
      str_echo(connfd);
      Close(connfd);
      exit(0);
    }
    Close(connfd);
  }
}
