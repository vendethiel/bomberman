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

void sleep_ms(int ms)
{
  Sleep((DWORD)ms);
}

/*
 * Under Unix, if you’re blocking on send() and your program is ignoring the SIGPIPE signal, it will return with a -1 when the remote peer disconnects, and errno will be EPIPE. Otherwise, your program will be sent the SIGPIPE signal, which will terminate your program if you don’t handle it. Under Winsock, the SIGPIPE/EPIPE functionality does not exist at all: send() will either return 0 for a normal disconnect or -1 for an abnormal disconnect, with WSAGetLastError() returning the same errors as in the recv() discussion above.
 *
 * https://tangentsoft.net/wskfaq/articles/bsd-compatibility.html
 */
void setup_signal_handlers(void)
{
}
