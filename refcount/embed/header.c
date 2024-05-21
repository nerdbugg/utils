#include "header.h"
#include "pointer_util.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void free_header(header *h) {
  printf("called free header\n");

  free(h); /* free memory */
}

void header_ref_destructor(struct ref *r) {
  /* get object ptr from field  ptr: container_of */
  header* h = container_of(r, header, ref);
  free_header(h);
}

header *alloc_header() {
  header *res = (header *)malloc(sizeof(struct header));
  res->name = NULL;
  res->value = NULL;
  ref_init(&(res->ref), header_ref_destructor);

  return res;
}


void get_header_ref(header *h) {
  ref_get(&h->ref);
}

void put_header_ref(header *h) {
  ref_put(&h->ref);
}

void print_header(header *h) {
  printf("Header: {\"%s\":\"%s\"}\n", h->name, h->value);
}

