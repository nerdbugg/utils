#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Fd {
  int fd_;
};
typedef struct Fd Fd;

Fd *create_fd();

void close_fd(Fd *fd);

#ifdef __cplusplus
}
#endif
