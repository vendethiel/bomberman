#ifndef PLATFORMS_COMMON_SOCKET_H_
#define PLATFORMS_COMMON_SOCKET_H_

#include "../../bomberman.h"

#ifndef PLATFORMS_SPECIFIC_SOCKET_H_
  #error Invalid platforms/common/socket.h usage: need to include specific file first.
#endif

typedef enum e_read_request {
  read_disconnect,
  read_ok,
  read_already_dc,
  read_none,
} read_request;

/* common */
void write_to(socket_holder, char*, size_t);

void socket_prepare(void);
void socket_cleanup(void);

/* server */
void accept_client(socket_holder*, socket_data*);
read_request read_client_request(socket_holder*, socket_data*, t_client_request*);
void select_clients(socket_data*, int numclients, socket_holder*);
void socket_prepare_data(socket_data*, int port, int numPlayers);

void write_to(socket_holder fd, char* data, size_t size);
void send_int(socket_holder sh, int i);
void send_char(socket_holder sh, char c);

/* client */
socket_holder connect_to_server(const char* addr, int port);
int  read_int(socket_holder sh, int* disconnected);
char  read_char(socket_holder sh, int* disconnected);
int  read_into(socket_holder sockfd, char* buffer, size_t left);


#endif
