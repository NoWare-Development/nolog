#include "log_thread.h"

#ifdef PLATFORM_WIN32

#include <Windows.h>

#include "log_queue.h"

static int is_running = 0;
static Queue *log_queue = 0;

void log_thread_print(void);

void log_thread_start(Queue *q) {
  is_running = 1;

  log_queue = q;

  HANDLE logger_thread = CreateThread(NULL, 0,
                                      (LPTHREAD_START_ROUTINE)log_thread_print,
                                      NULL, 0, NULL);
}

void log_thread_stop(void) {
  Sleep(1000);
  log_queue = 0;
  is_running = 0;
}

void log_thread_print(void) {
  LogMessage out = {0};
  while (is_running) {
    Sleep(1);
    if (!log_queue) continue;

    while (log_queue_dequeue(log_queue, &out))
      fprintf(out.level == 0 ? stderr : stdout, out.message);
  }
}

#endif // PLATFORM_WIN32
