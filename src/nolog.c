#include <nolog.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>

#include "log_thread.h"
#include "log_queue.h"

static Queue log_queue = {0};

int string_format(char *dest, const char *format, ...);
int string_format_v(char *dest, const char *format, void *va_listp);

void init_logger(void) {
  log_queue_init(&log_queue);
  log_thread_start(&log_queue);
}

void stop_logger(void) {
  log_thread_stop();
  log_queue_destroy(&log_queue);
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

  log_queue_enqueue(&log_queue, q_msg);
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
