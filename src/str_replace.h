#ifndef MARIA_STR_REPLACE_H
#define MARIA_STR_REPLACE_H

#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "logger/maria_logger.h"

char *str_replace(const char *orig, const char *rep, const char *with);

#endif
