#include "header.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct worker_thr_args {
  header** headers;
  int n;
};
typedef struct worker_thr_args worker_thr_args;

void* worker_thr(void* args) {
  worker_thr_args* arg = (worker_thr_args*)args;
  for (int i=0; i<arg->n; i++) {
    get_header_ref(arg->headers[i]);
    header *h=arg->headers[i];
    print_header(h);
  }

  for(int i=0;i<arg->n;i++) {
    // NOTE: get_ref is called in above loop
    header* h = arg->headers[i];
    sleep(rand()%10); /* wait for seconds */
    // NOTE: sub-thread put ref
    put_header_ref(h);
  }

  return NULL;
}

int main(int argc, char *argv[]) { 
  header* headers[3];
  headers[0] = alloc_header();
  headers[0]->name = "name";
  headers[0]->value = "joe";
  headers[1] = alloc_header();
  headers[1]->name = "age";
  headers[1]->value = "22";
  headers[2] = alloc_header();
  headers[2]->name = "weight";
  headers[2]->value = "150";

  // NOTE: get ref here, extend the life time safely
  // NOTE: read shared_ptr impl
  worker_thr_args args = {headers, 3};
  pthread_t t;
  pthread_create(&t, NULL, worker_thr, &args);

  // ending main thread lifetime
  for(int i=0;i<3;i++) {
    put_header_ref(headers[i]);
  }

  pthread_join(t, NULL);

  /*
  cleaning, main thread put ref
  for(int i=0;i<3;i++) {
    put_header_ref(headers[i]);
  }
  */

  return EXIT_SUCCESS; 
}
