#include "thread.h"
#include "server.h"
#include "client.h"
#include "server_state.h"

int is_running(t_server* server)
{
  if (game_is_finish(&server->game, -1))
    return 0;

  mutex_lock(&server->mutex);
  int ret = server->running;
  mutex_unlock(&server->mutex);
  return ret;
}

void set_running(t_server* server, int value)
{
  mutex_lock(&server->mutex);
  server->running = value;
  mutex_unlock(&server->mutex);
}
