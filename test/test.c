#include <nolog.h>

int main(void) {
  LOG_ERROR("test error message: %d %d", 12, 5);
  LOG_WARN("test warning message: %s", "trace message");
  LOG_INFO("test info message: %c", 'a');
  LOG_TRACE("test trace message: %.2f", 3.14);

  return 0;
}
