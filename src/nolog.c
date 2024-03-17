#include <nolog.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>

#include <unistd.h>
#include <pthread.h>

#define MAX_LOG_MESSAGE_SIZE 4096

typedef struct {
  LogLevel level;
  char message[MAX_LOG_MESSAGE_SIZE];
} LogMessage;

typedef struct _node {
  LogMessage message;
  struct _node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
} Queue;

int is_running = 0;
static Queue log_queue = {0};

void init_queue(Queue *q);
int enqueue(Queue *q, LogMessage message);
int dequeue(Queue *q, LogMessage *out);
void *print_log(void *arg);

int string_format(char *dest, const char *format, ...);
int string_format_v(char *dest, const char *format, void *va_listp);

void init_logger(void) {
  is_running = 1;

  init_queue(&log_queue);

  pthread_t logger_thread;
  pthread_create(&logger_thread, NULL, print_log, NULL);
}

void stop_logger(void) {
  sleep(1);
  is_running = 0;
}

void log_message(LogLevel level, const char *msg, ...) {
  const char *level_strings[4] = {
    "[ERROR]: ", "[WARN ]: ", "[INFO ]: ", "[TRACE]: "
  };

  char out_message[MAX_LOG_MESSAGE_SIZE];
  memset(out_message, 0, MAX_LOG_MESSAGE_SIZE);

  __builtin_va_list arg_ptr;
  va_start(arg_ptr, msg);
  string_format_v(out_message, msg, arg_ptr);
  va_end(arg_ptr);

  string_format(out_message, "%s%s\n", level_strings[level], out_message);

  LogMessage q_msg;
  q_msg.level = level;
  snprintf(q_msg.message, MAX_LOG_MESSAGE_SIZE, "%s", out_message);

  enqueue(&log_queue, q_msg);
}

int string_format_v(char *dest, const char *format, void *va_listp) {
  if (dest) {
    char buffer[MAX_LOG_MESSAGE_SIZE];
    int written = vsnprintf(buffer, MAX_LOG_MESSAGE_SIZE, format, va_listp);
    buffer[written] = 0;
    memcpy(dest, buffer, written + 1);

    return written;
  }

  return -1;
}

int string_format(char *dest, const char *format, ...) {
  if (dest) {
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, format);
    int written = string_format_v(dest, format, arg_ptr);
    va_end(arg_ptr);

    return written;
  }

  return -1;
}

// Queue stuff
void init_queue(Queue *q) {
  q->head = 0;
  q->tail = 0;
}

int enqueue(Queue *q, LogMessage message) {
  Node *new_node = malloc(sizeof(Node));
  if (!new_node) return 0;
  new_node->message = message;
  new_node->next = 0;
  if (q->tail) q->tail->next = new_node;
  q->tail = new_node;
  if (!q->head) q->head = new_node;
  return 1;
}

int dequeue(Queue *q, LogMessage *out) {
  if (!q->head) return 0;

  Node *tmp = q->head;
  *out = tmp->message;
  q->head = q->head->next;
  if (!q->head) q->tail = 0;
  free(tmp);
  return 1;
}

void *print_log(void *arg) {
  LogMessage out = {0};
  while (is_running) {
    while (dequeue(&log_queue, &out)) {
      fprintf(out.level == LOG_LEVEL_ERROR ? stderr : stdout, out.message);
    }
    sleep(0.001f);
  }
  return 0;
}
