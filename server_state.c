#include <pthread.h>
#include "server_state.h"

static pthread_mutex_t mutex;

size_t lock(void)
{
	if (pthread_mutex_init(&mutex, NULL) != 0)
		return (0);
  	if (pthread_mutex_lock(&mutex))
		return (0);

	return (1);
}

size_t unlock(void)
{
	return (pthread_mutex_unlock(&mutex));
}

int is_running(t_server* server)
{
  lock();
  ret = server->running;
  unlock();
  return ret;
}

void set_running(t_server* server, int value)
{
  lock();
  server->running = value;
  unlock();
}
