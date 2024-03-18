#include "log_queue.h"

#include <stdlib.h>

void log_queue_init(Queue *q) {
  q->head = 0;
  q->tail = 0;
  q->valid = 1;
}

void log_queue_destroy(Queue *q) {
  if (!q->valid) return;

  q->head = 0;
  q->tail = 0;

  q->valid = 0;
}

int log_queue_enqueue(Queue *q, LogMessage message) {
  Node *new_node = malloc(sizeof(Node));
  if (!new_node) return 0;
  new_node->message = message;
  new_node->next = 0;
  if (q->tail) q->tail->next = new_node;
  q->tail = new_node;
  if (!q->head) q->head = new_node;
  return 1;
}

int log_queue_dequeue(Queue *q, LogMessage *out) {
  if (!q->head) return 0;

  Node *tmp = q->head;
  *out = tmp->message;
  q->head = q->head->next;
  if (!q->head) q->tail = 0;
  free(tmp);
  return 1;
}
