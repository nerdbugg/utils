#include "header.h"

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

header *alloc_header() {
  header *res = (header *)malloc(sizeof(struct header));
  res->name = NULL;
  res->value = NULL;
  pthread_mutex_init(&res->reflock, NULL);
  res->refcount = 1;

  printf("[init] refcount: %d\n", res->refcount);
  return res;
}

static void free_header(header *h) { 
  printf("called free header\n");

  assert(h->refcount==0);
  pthread_mutex_destroy(&h->reflock); /* member destructor is called */
  free(h); /* free memory */
}

void get_header_ref(header *h) {
  pthread_mutex_lock(&h->reflock);
  h->refcount++;
  pthread_mutex_unlock(&h->reflock);

  printf("[get_ref] refcount: %d\n", h->refcount);
}

void put_header_ref(header *h) {
  bool need_destroied = false;

  pthread_mutex_lock(&h->reflock);
  h->refcount--;
  if(h->refcount==0) {
    need_destroied = true;
  }
  pthread_mutex_unlock(&h->reflock);

  if(need_destroied) {
    free_header(h);
    printf("[put_ref] refcount: 0\n");
  } else {
    printf("[put_ref] refcount: %d\n", h->refcount);
  }
}

void print_header(header *h) {
  printf("Header: {\"%s\":\"%s\"}\n", h->name, h->value);
}

