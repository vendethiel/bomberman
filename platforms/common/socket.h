#ifndef PLATFORMS_COMMON_SOCKET_H_
#define PLATFORMS_COMMON_SOCKET_H_

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
read_request read_client_request(socket_holder*, socket_data*, char*);
void select_clients(socket_data*, int numclients, socket_holder*);
void socket_prepare_data(socket_data*, int port);

/* client */
socket_holder connect_to_server(const char* addr, int port);
char*  read_from(socket_holder sh, size_t left, int* disconnected);


#endif
