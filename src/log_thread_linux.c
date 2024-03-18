#include "log_thread.h"

#ifdef PLATFORM_LINUX

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#include "log_queue.h"

static int is_running = 0;
static Queue *log_queue = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void log_thread_start(Queue *q) {
  is_running = 1;

  log_queue = q;

  pthread_t logger_thread;
  pthread_create(&logger_thread, NULL, log_thread_print, NULL);
}

void log_thread_stop(void) {
  sleep(1);
  log_queue = 0;
  is_running = 0;
}

void *log_thread_print(void *) {
  LogMessage out = {0};
  while (is_running) {
    sleep(0.001f);
    if (!log_queue) continue;

    pthread_mutex_lock(&lock);
    while (log_queue_dequeue(log_queue, &out))
      fprintf(out.level == 0 ? stderr : stdout, out.message);
    pthread_mutex_unlock(&lock);
  }
  return 0;
}

#endif // PLATFORM_LINUX
