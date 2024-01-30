#include <sys/time.h>
#include <stdbool.h>

struct profiler_t {
  struct timespec begin;
  struct timespec end;
  struct timespec elapsed;
  bool enabled;
};
typedef struct profiler_t profiler_t;

enum event_type {
#define EVENT_ENUM(x) x,
#include "event.def"
};

extern profiler_t global_profilers[MAX_PROFILER_NUM];



void profiler_begin(profiler_t *p);
void profiler_end(profiler_t *p);
void profiler_dump(profiler_t* profilers, char* name, bool full);
