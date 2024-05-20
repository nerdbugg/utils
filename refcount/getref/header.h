#include <pthread.h>

struct header {
  const char *name;
  const char *value;

  pthread_mutex_t reflock;
  int refcount;
};
typedef struct header header;

header *alloc_header();
void get_header_ref(header *h);
void put_header_ref(header *h);

void print_header(header *h);
