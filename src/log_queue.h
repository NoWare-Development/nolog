#ifndef LOG_QUEUE_H_
#define LOG_QUEUE_H_

#include "types.h"

void log_queue_init(Queue *q);
void log_queue_destroy(Queue *q);
int log_queue_enqueue(Queue *q, LogMessage message);
int log_queue_dequeue(Queue *q, LogMessage *out);

#endif // LOG_QUEUE_H_
