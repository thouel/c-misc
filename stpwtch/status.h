#include <stdio.h>

typedef struct {
  // 0 = not running, 1 = running, 2 = paused
  short isRunning;
  short hours;
  short minutes;
  short seconds;
} status_t;