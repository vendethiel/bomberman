#include "socket_server.h"

void socket_cleanup(void)
{
  WSACleanup();
}