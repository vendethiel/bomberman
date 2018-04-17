#ifndef THREAD_H
#define THREAD_H

#if defined(_WIN32) || defined(WIN32)
  #include "platforms/windows/thread.h"
#elif defined(__linux__) || defined(__APPLE__)
#include "platforms/posix/thread.h"
#else
  #error Unsupported platform
#endif

//#include "platforms/common/thread.h"

void mutex_lock(mutex_t*);
void mutex_unlock(mutex_t*);

/* returns 1 if init correctly, 0 otherwise */
int mutex_init(mutex_t*);

void sleep_ms(int ms);
void setup_signal_handlers(void);

#endif
