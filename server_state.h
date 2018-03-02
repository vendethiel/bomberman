#ifndef SERVER_STATE_H_
#define SERVER_STATE_H_

#include "server.h"

size_t	lock(void);
size_t	unlock(void);
int is_running(t_server* server);
void set_running(t_server* server, int value);


#endif
