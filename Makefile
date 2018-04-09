SRC = $(wildcard *.c)

ifeq ($(OS),Windows_NT)
	SRC+=platforms/win/socket_client.c platforms/win/socket_server.c
else
	SRC+=platforms/posix/socket_client.c platforms/posix/socket_server.c
endif

OBJ = $(SRC:.c=.o)

LIBS = `sdl2-config --libs`

CFLAGS += -Wall -Wextra -Wpedantic -std=c11 `sdl2-config --cflags` -g

NAME = bomberman

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LIBS) -lSDL2_image

.PHONY: clean fclean

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: clean all
