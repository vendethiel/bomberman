#include <process.h>
#include "../../err.h"
#include "../../thread.h"

void mutex_lock(mutex_t* m)
{
  EnterCriticalSection(m);
}

void mutex_unlock(mutex_t* m)
{
  LeaveCriticalSection(m);
}

int mutex_init(mutex_t* m)
{
  InitializeCriticalSection(m);
  return 1 /* always works! */;
}

void mutex_cleanup(mutex_t* m)
{
  DeleteCriticalSection(m);
}

void sleep_ms(int ms)
{
  Sleep((DWORD)ms);
}

struct windows_thread_wrapper
{
  thread_fn fn;
  void* data;
};

/* wraps the thread function to return 0 */
static unsigned __stdcall wrap_thread_create(void* tw)
{
  struct windows_thread_wrapper* w = tw;
  w->fn(w->data);
  free(tw);
  return 0;
}

void thread_create(thread_t* t, thread_fn fn, void* data)
{
  struct windows_thread_wrapper *tw;
  tw = malloc(sizeof *tw);
  if (!tw)
    ERR_MSG("Unable to alloc thread wrapper");
  tw->fn = fn;
  tw->data = data;
  *t = (HANDLE)_beginthreadex(
    NULL /* security */,
    0 /* stack size */,
    wrap_thread_create,
    tw,
    0 /* initflag */,
    NULL /* thread id */
  );
  if (0 == *t)
    ERR_MSG("Unable to _beginthreadex");
}

void thread_join(thread_t tid)
{
  WaitForSingleObject(tid, INFINITE);
}

/*
 * Under Unix, if you’re blocking on send() and your program is ignoring the SIGPIPE signal, it will return with a -1 when the remote peer disconnects, and errno will be EPIPE. Otherwise, your program will be sent the SIGPIPE signal, which will terminate your program if you don’t handle it. Under Winsock, the SIGPIPE/EPIPE functionality does not exist at all: send() will either return 0 for a normal disconnect or -1 for an abnormal disconnect, with WSAGetLastError() returning the same errors as in the recv() discussion above.
 *
 * https://tangentsoft.net/wskfaq/articles/bsd-compatibility.html
 */
void setup_signal_handlers(void)
{
}
