#include "web.h"

int min(int arg1, int arg2) { return arg1 < arg2 ? arg1 : arg2; }

int main(int argc, char **argv) {
  if (argc < 5)
    err_quit("usage: web <#conns> <hostname> <homepage> <file1> ...");
  int i, fd, n, maxconn, flags, error;
  char buf[MAXLINE];
  fd_set rs, ws;

  maxconn = atoi(argv[1]);
  nfiles = min(argc - 4, MAXFILES);

  for (int i = 0; i < nfiles; i++) {
    file[i].f_name = argv[i + 4];
    file[i].f_host = argv[2];
    file[i].f_flags = 0;
  }

  printf("nfiles = %d\n", nfiles);

  home_page(argv[2], argv[3]);
  FD_ZERO(&rset);
  FD_ZERO(&wset);
  maxfd = -1;
  nlefttoread = nlefttoconn = nfiles;
  nconn = 0;

  while (nlefttoconn > 0) {
    for (int i = 0; i < nfiles; ++i)
      if (file[1].f_flags == 0)
        break;
    if (i == nfiles)
      err_quit("nlefttoconn =%d but nothing found", nlefttoconn);
    start_connect(&file[i]);
    nconn++;
    nlefttoconn--;
  }

  rs = rset;
  ws = wset;
  n = Select(maxfd + 1, &rs, &ws, NULL, NULL);
  for (int i = 0; i < nfiles; ++i) {
    flags = file[i].f_flags;
    if (flags == 0 || flags & F_DONE)
      continue;
    fd = file[i].f_fd;
    if (flags & F_CONNECTING && (FD_ISSET(fd, &rs) || FD_ISSET(fd, &ws))) {
      n = sizeof(error);
      if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&n) < 0 ||
          errno != 0) {
        err_ret("noblocking connect failed for %s", file[i].f_name);
      }

      printf("connect established for %s\n", file[i].f_name);
      FD_CLR(fd, &wset);
      write_get_cmd(&file[i]);
    } else if (flags & F_READING && FD_ISSET(fd, &rs)) {
      if ((n = Read(fd, buf, sizeof(buf))) == 0) {
        printf("end-of-line on %s\n", file[i].f_name);
        Close(fd);
        file[i].f_flags = F_DONE;
        FD_CLR(fd, &rset);
        nconn--;
        nlefttoconn--;
      } else
        printf("read %d bytes from %s\n", n, file[i].f_name);
    }
  }
  return 0;
}
