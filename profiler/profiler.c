#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "profiler.h"

profiler_t global_profilers[MAX_PROFILER_NUM];

char *event_type_tostr(enum event_type e) {
  switch (e) {
#define EVENT_ENUM(x) case x: return #x;
#include "event.def"
    default:
      return "undefined event";
  }
}

void timespec_tostr(struct timespec *ts, char buf[], size_t len);
int timespec_diff(struct timespec *ts1, struct timespec *ts2,
                  struct timespec *res);

void time_get(struct timespec *tp) { clock_gettime(CLOCK_REALTIME, tp); }

void profiler_begin(profiler_t *p) {
  time_get(&(p->begin));
  if(p->enabled) {
    printf("conflict!\n");
    printf("profiler name: %s\n", event_type_tostr(p-global_profilers));
  }
  p->enabled = true;
}

void profiler_end(profiler_t *p) {
  time_get(&(p->end));
  if (p->enabled) {
    timespec_diff(&(p->begin), &(p->end), &(p->elapsed));
    p->enabled = false;
    p->begin.tv_sec=0;
    p->begin.tv_nsec=0;
  }
}

void profiler_dump(profiler_t* profilers, char* name, bool full){
  profiler_t *ps = profilers;

#ifdef DEBUG
  printf("[warning] executable is compiled under DEBUG mode!!!\n");
#endif

  printf(">>>>>--------------------\r\n");
  printf("Profiler name: <%s>\n", name);
  printf("Profiler analysis:\r\n");
  for (int i = 0; i < MAX_PROFILER_NUM; i++) {
    char buf[32];
    profiler_t *profiler = &(profilers[i]);

    if(full==false) {
      struct timespec *temp = &(profilers[i].elapsed);
      if(temp->tv_nsec==0&&temp->tv_sec==0) {
        continue;
      }
    }

    timespec_tostr(&(profilers[i].elapsed), buf, 32);
    printf("%-32s %s (raw data: %ld s, %ld ns)\r\n", event_type_tostr(i), buf,
           profiler->elapsed.tv_sec, profiler->elapsed.tv_nsec);
  }
  printf("<<<<<--------------------\r\n");
}

void timespec_tostr(struct timespec *ts, char buf[], size_t len) {
  double time;
  int res;
  // ms
  double ms = ts->tv_sec * 1e3 + ts->tv_nsec / 1e6;
  time = ms;
  res = snprintf(buf, len, "%.3f ms", time);
#ifdef PROFILER_US
  // us
  double us = ts->tv_sec * 1e6 + ts->tv_nsec / 1e3;
  time = us;
  res = snprintf(buf, len, "%.3f us", time);
#endif
  return;
}

int timespec_diff(struct timespec *ts1, struct timespec *ts2,
                  struct timespec *res) {
  if (ts2->tv_nsec < ts1->tv_nsec) {
    if (ts2->tv_sec > ts1->tv_sec) {
      res->tv_nsec = 1000000000 - ts1->tv_nsec + ts2->tv_nsec;
      res->tv_sec = ts2->tv_sec - 1 - ts1->tv_sec;
    } else {
      printf("[warning] start time stamp is larger than end!!!\n");
      printf("ts1: %ld s, %ld ns\n", ts1->tv_sec, ts1->tv_nsec);
      printf("ts2: %ld s, %ld ns\n", ts2->tv_sec, ts2->tv_nsec);
      return -1;
    }
  } else {
    if (ts2->tv_sec >= ts1->tv_sec) {
      res->tv_sec = ts2->tv_sec - ts1->tv_sec;
      res->tv_nsec = ts2->tv_nsec - ts1->tv_nsec;
    } else {
      printf("[warning] start time stamp is larger than end!!!\n");
      printf("ts1: %ld s, %ld ns\n", ts1->tv_sec, ts1->tv_nsec);
      printf("ts2: %ld s, %ld ns\n", ts2->tv_sec, ts2->tv_nsec);
      return -1;
    }
  }

  return 0;
}

