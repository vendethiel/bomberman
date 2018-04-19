#include "../../err.h"
#ifndef __MINGW32__
  #include <WS2tcpip.h>
#endif
#include "../../socket.h"

SOCKET connect_to_server(const char* addr, int port)
{
  socket_holder sh;
  struct sockaddr_in serv;

  printf("Connecting to %s:%i\n", addr, port);
  sh = socket(AF_INET, SOCK_STREAM, 0);
  if (INVALID_SOCKET == sh)
    ERR_MSG("Could not open socket, er==\n", WSAGetLastError());
  ZeroMemory(&serv, sizeof serv);
  serv.sin_family = AF_INET;
  serv.sin_port = htons(port);
#ifdef __MINGW32__
  serv.sin_addr.s_addr = inet_addr(addr);
#else
  if (1 != InetPton(AF_INET, addr, &serv.sin_addr))
    ERR_MSG("InetPton failed");
#endif
  if (SOCKET_ERROR == connect(sh, (SOCKADDR*)&serv, sizeof serv))
    ERR_MSG("Connect returned while trying to connect to %s:%d -1. errno=%d\n", addr, port, WSAGetLastError());
  u_long mode = 1; /* nonblocking mode */
  ioctlsocket(sh, FIONBIO, &mode);
  return sh;
}
