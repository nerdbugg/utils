#include <pthread.h>

#include "ref.h"

struct header {
  const char *name;
  const char *value;

  struct ref ref;
};
typedef struct header header;

header *alloc_header();
void get_header_ref(header *h);
void put_header_ref(header *h);

void print_header(header *h);
