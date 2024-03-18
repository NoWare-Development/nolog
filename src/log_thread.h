#ifndef LOG_THREAD_H_
#define LOG_THREAD_H_

#include "types.h"

void log_thread_start(Queue *q);
void log_thread_stop(void);
void *log_thread_print(void *);

#endif // LOG_THREAD_H_
