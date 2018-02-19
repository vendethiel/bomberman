#include <unistd.h>
#include <sys/time.h>
#include "client_actions.h"

void handle_action(SDL_KeyboardEvent* key, int sockfd, t_player_info* infos)
{
  (void)infos; /* might not be necessary */
  t_client_request *req = calloc(sizeof *req, 1);
  
	req->magic = 42;

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
    write(sockfd, (char*)req, sizeof *req);
  free(req);
}
