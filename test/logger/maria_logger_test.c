#include <criterion/criterion.h>
#include "logger/maria_logger.h"

Test(maria_logger, maria_log_message) {
  maria_log("test message libnss-maria");
}
