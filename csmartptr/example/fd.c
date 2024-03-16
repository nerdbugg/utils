#include <stdio.h>

#include "fd.h"

Fd *create_fd() {
  Fd *fd = malloc(sizeof(Fd));
  fd->fd_ = open("/dev/null", O_RDWR);
  return fd;
}

void close_fd(Fd *fd) { 
  close(fd->fd_); 
  printf("fd closed\n");
}
