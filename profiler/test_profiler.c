#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "profiler.h"

int main(int argc, char *argv[]) {
  profiler_begin(&(global_profilers[E2E]));
  printf("Hello world!\n");
  profiler_end(&(global_profilers[E2E]));

  profiler_dump((profiler_t *)global_profilers, "global", true);
  return 0;
}
