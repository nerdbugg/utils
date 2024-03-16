#include <cstdio>

#include "fd.h"
#include "c_smart_ptr.h"

using FDSmartPtr = CSmartPtr<Fd, close_fd>;

int main (int argc, char *argv[]) {
  Fd* fd = create_fd();

  {
    printf("put in SmartPtr\n");
    FDSmartPtr fd_ptr(fd);
    printf("leave scope\n");
  }

  return 0;
}
