SERVER_SRC = server.c
CLIENT_SRC = client.c
SERVER_BONUS_SRC = server_bonus.c
CLIENT_BONUS_SRC = client_bonus.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_BONUS_OBJ = $(SERVER_BONUS_SRC:.c=.o)
CLIENT_BONUS_OBJ = $(CLIENT_BONUS_SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = cc

LIBFTDIR = includes/libft
LIBFTNAME = $(LIBFTDIR)/libft.a

all: server client

bonus: server_bonus client_bonus

server: $(SERVER_OBJ) $(LIBFTNAME)
	$(CC) $(FLAGS) $(SERVER_OBJ) -L$(LIBFTDIR) -lft -o server

client: $(CLIENT_OBJ) $(LIBFTNAME)
	$(CC) $(FLAGS) $(CLIENT_OBJ) -L$(LIBFTDIR) -lft -o client

server_bonus: $(SERVER_BONUS_OBJ) $(LIBFTNAME)
	$(CC) $(FLAGS) $(SERVER_BONUS_OBJ) -L$(LIBFTDIR) -lft -o server_bonus

client_bonus: $(CLIENT_BONUS_OBJ) $(LIBFTNAME)
	$(CC) $(FLAGS) $(CLIENT_BONUS_OBJ) -L$(LIBFTDIR) -lft -o client_bonus

$(LIBFTNAME):
	make -C $(LIBFTDIR)

%.o: %.c
	$(CC) $(FLAGS) -I$(LIBFTDIR) -c $< -o $@

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ) $(SERVER_BONUS_OBJ) $(CLIENT_BONUS_OBJ)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f server client server_bonus client_bonus

re: fclean all

.PHONY: all bonus clean fclean re
