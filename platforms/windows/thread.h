#ifndef PLATFORMS_WINDOWS_THREAD_H
#define PLATFORMS_WINDOWS_THREAD_H

#define _WINSOCKAPI_ // prevent windows.h from including winsock
#include <windows.h>

typedef HANDLE thread_t;
typedef CRITICAL_SECTION mutex_t;

#endif
