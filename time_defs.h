// Some helper logic for working with times.

#pragma once
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

static OptionalText_t _local_timezone = NONE_TEXT;

static void set_local_timezone(Text_t tz) {
  setenv("TZ", Text$as_c_string(tz), 1);
  _local_timezone = tz;
  tzset();
}

#define WITH_TIMEZONE(tz, body)                                                \
  ({                                                                           \
    if (tz.length >= 0) {                                                      \
      OptionalText_t old_timezone = _local_timezone;                           \
      set_local_timezone(tz);                                                  \
      body;                                                                    \
      set_local_timezone(old_timezone);                                        \
    } else {                                                                   \
      body;                                                                    \
    }                                                                          \
  })
