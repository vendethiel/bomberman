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

void mutex_cleanup(mutex_t* m)
{
  pthread_mutex_destroy(m);
}

struct posix_thread_wrapper
{
  thread_fn fn;
  void* data;
};

/* wraps the thread function to return NULL */
static void* wrap_thread_create(void* tw)
{
  struct posix_thread_wrapper* w = tw;
  w->fn(w->data);
  return NULL;
}

void thread_create(thread_t* tid, thread_fn fn, void* data)
{
  struct posix_thread_wrapper tw;
  tw.fn = fn;
  tw.data = data;
  pthread_create(tid, NULL, wrap_thread_create, &tw);
}

void thread_join(thread_t tid)
{
  void *discard_return;
  pthread_join(tid, &discard_return);
}

void sleep_ms(int ms)
{
  usleep(ms * 1000);
}

void setup_signal_handlers(void)
{
  signal(SIGPIPE, SIG_IGN); /* discard SIGPIPE signals */
}
