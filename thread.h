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
void mutex_init(mutex_t*);

#endif THREAD_H
