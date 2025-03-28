NAME = minitalk

SERVER = server

CLIENT = client

SERVER_SRCS = server.c msg.c utils_server.c

CLIENT_SRCS = client.c utils_client.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(CLIENT) $(SERVER)

$(SERVER): $(SERVER_SRCS)
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o $(SERVER)

$(CLIENT): $(CLIENT_SRCS)
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o $(CLIENT)

clean:

fclean:
	rm -f $(CLIENT) $(SERVER)

re: fclean all

bonus: all

.PHONY: clean fclean re bonus all
