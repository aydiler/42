NAME = libftprintf.a
LIBFTDIR = ./libft
LIBFTNAME = libft.a

SERVER_SRC = server.c
CLIENT_SRC = client.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = cc

all: server client

server: $(SERVER_OBJ) $(LIBFTNAME)
	$(CC) $(FLAGS) $(SERVER_OBJ) $(LIBFTNAME) -o server

client: $(CLIENT_OBJ) $(LIBFTNAME)
	$(CC) $(FLAGS) $(CLIENT_OBJ) $(LIBFTNAME) -o client

$(LIBFTNAME):
	make -C $(LIBFTDIR) all

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f server client

re: fclean all

.PHONY: all clean fclean re