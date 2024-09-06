SERVER_SRC = server.c
CLIENT_SRC = client.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = cc

LIBFTDIR = includes/libft
LIBFTNAME = $(LIBFTDIR)/libft.a

all: server client

server: $(SERVER_OBJ) $(LIBFTNAME)
	$(CC) $(FLAGS) $(SERVER_OBJ) -L$(LIBFTDIR) -lft -o server

client: $(CLIENT_OBJ) $(LIBFTNAME)
	$(CC) $(FLAGS) $(CLIENT_OBJ) -L$(LIBFTDIR) -lft -o client

$(LIBFTNAME):
	make -C $(LIBFTDIR)

%.o: %.c
	$(CC) $(FLAGS) -I$(LIBFTDIR) -c $< -o $@

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f server client

re: fclean all

.PHONY: all clean fclean re