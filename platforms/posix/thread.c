#include <unistd.h>
#include <signal.h>
#include "../../thread.h"

void mutex_lock(mutex_t* m)
{
  pthread_mutex_lock(m);
}

void mutex_unlock(mutex_t* m)
{
  pthread_mutex_unlock(m);
}

int mutex_init(mutex_t* m)
{
  return 0 == pthread_mutex_init(m, NULL);
}

void sleep_ms(int ms)
{
  usleep(ms * 1000);
}

void setup_signal_handlers(void)
{
  signal(SIGPIPE, SIG_IGN); /* discard SIGPIPE signals */
}
