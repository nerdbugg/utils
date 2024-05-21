#include "ref.h"
#include <stdio.h>

void ref_init(struct ref *r, void (*release)(struct ref *r)) {
  atomic_init(&(r->count), 1);
  r->release = release;
}
void ref_get(struct ref *r) {
  int old_count = atomic_fetch_add(&r->count, 1);
}
void ref_put(struct ref *r) {
  atomic_fetch_sub(&r->count, 1);

  int cur_count = atomic_load(&r->count);

  printf("ref_put: %d\n", cur_count);

  if (cur_count == 0) {
    r->release(r);
  }
}

