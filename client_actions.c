#include "client_actions.h"
#include "socket.h"

void handle_action(SDL_KeyboardEvent* key, socket_holder sockfd, t_player_info* infos)
{
  (void)infos; /* might not be necessary */
  t_client_request req;
  req.y_pos = req.x_pos = req.command = 0;
  
  switch (key->keysym.sym)
  {
    case SDLK_UP:
      req.y_pos = -1;
    break;
    case SDLK_DOWN:
      req.y_pos = 1;
    break;
    case SDLK_LEFT:
      req.x_pos = -1;
    break;
    case SDLK_RIGHT:
      req.x_pos = 1;
    break;

    case SDLK_SPACE:
      req.command = 1;
    break;

    default:
      return;
  }
  send_int(sockfd, req.x_pos);
  send_int(sockfd, req.y_pos);
  send_int(sockfd, req.command);
}
