#include <nolog.h>

#include <stdio.h>

int main(void) {
  init_logger();

  LOG_ERROR("test error message: %d %d", 12, 5);
  LOG_WARN("test warning message: \"%s\"", "warning message");
  LOG_INFO("test info message: %c", 'a');
  LOG_TRACE("test trace message: %.2f", 3.14);

  stop_logger();

  return 0;
}
