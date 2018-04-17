#ifndef SOCKET_H_
#define SOCKET_H_

#if defined(_WIN32) || defined(WIN32)
  #include "platforms/windows/socket.h"
#elif defined(__linux__) || defined(__APPLE__)
  #include "platforms/posix/socket.h"
#else
  #error Unsupported platform
#endif

#include "platforms/common/socket.h"

#endif

