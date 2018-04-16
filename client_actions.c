#include "client_actions.h"
#include "socket.h"

void handle_action(SDL_KeyboardEvent* key, socket_holder sockfd, t_player_info* infos)
{
  (void)infos; /* might not be necessary */
  t_client_request *req = calloc(sizeof *req, 1);
  
  switch (key->keysym.sym)
  {
    case SDLK_UP:
      req->y_pos = -1;
    break;
    case SDLK_DOWN:
      req->y_pos = 1;
    break;
    case SDLK_LEFT:
      req->x_pos = -1;
    break;
    case SDLK_RIGHT:
      req->x_pos = 1;
    break;

    case SDLK_SPACE:
      req->command = 1;
    break;

    default:
      free(req);
      req = NULL;
  }
  if (req)
    write_to(sockfd, (char*)req, sizeof *req);
  free(req);
}
