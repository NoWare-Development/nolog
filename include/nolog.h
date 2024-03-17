#ifndef NOLOG_H_
#define NOLOG_H_

typedef enum {
  LOG_LEVEL_ERROR = 0,
  LOG_LEVEL_WARN = 1,
  LOG_LEVEL_INFO = 2,
  LOG_LEVEL_TRACE = 3
} LogLevel;

void init_logger(void);
void stop_logger(void);
void log_message(LogLevel level, const char *message, ...);

#define LOG_ERROR(msg, ...) log_message(LOG_LEVEL_ERROR, msg, ##__VA_ARGS__)
#define LOG_WARN(msg, ...) log_message(LOG_LEVEL_WARN, msg, ##__VA_ARGS__)
#define LOG_INFO(msg, ...) log_message(LOG_LEVEL_INFO, msg, ##__VA_ARGS__)
#define LOG_TRACE(msg, ...) log_message(LOG_LEVEL_TRACE, msg, ##__VA_ARGS__)

#endif // NOLOG_H_
