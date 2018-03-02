#include <pthread.h>
#include "server.h"
#include "server_state.h"

int is_running(t_server server)
{
  int ret;

  pthread_mutex_lock(&server.mutex);
  ret = server.running;
  pthread_mutex_unlock(&server.mutex);
  return ret;
}

void set_running(t_server server, int value)
{
  pthread_mutex_lock(&server.mutex);
  server.running = value;
  pthread_mutex_unlock(&server.mutex);
}
