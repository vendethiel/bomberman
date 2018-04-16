#include "../../thread.c"

void mutex_lock(mutex_t* m)
{
  EnterCriticalSection(m);
}

void mutex_unlock(mutex_t* m)
{
  LeaveCriticalSection(m);
}

void mutex_init(mutex_t* m)
{
  InitializeCriticalSection(m);
}