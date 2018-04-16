#include "../../thread.h"

void mutex_lock(mutex_t* m)
{
  pthread_mutex_lock(m);
}

void mutex_unlock(mutex_t* m)
{
  pthread_mutex_unlock(m);
}

void mutex_init(mutex_t* m)
{
  pthread_mutex_init(m, NULL);
}