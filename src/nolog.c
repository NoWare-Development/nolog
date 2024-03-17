#include <nolog.h>

#include <stdio.h>
#include <stdarg.h>
#include <memory.h>

#define MAX_LOG_MESSAGE_SIZE 4096

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

  fprintf(level == LOG_LEVEL_ERROR ? stderr : stdout, out_message);
}
