#ifndef ERR_H_
#define ERR_H_

#include <stdio.h>

#define ERR_MSG(...) { fprintf(stderr, __VA_ARGS__); exit(1); }

#endif
