NAME		= pipex

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBS		= -L./includes/libft -lft \
			  -L./includes/printf -lprintf \

INCLUDES	= -I./includes \
			  -I./includes/libft \
			  -I./includes/printf \

SOURCE		= ./source/

SRC = $(addprefix $(SOURCE), \
    pipex.c pipex_utils.c \
)

OBJ = $(SRC:%.c=%.o)

all: libft printf $(NAME)

libft:
	make -C ./includes/libft

printf:
	make -C ./includes/printf

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $(<:%.c=%.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

clean:
	rm -rf $(OBJ)
	rm -rf ./a.out
	make clean -C ./includes/libft
	make clean -C ./includes/printf

fclean: clean<w
	rm -rf $(NAME)
	make fclean -C ./includes/libft
	make fclean -C ./includes/printf

re: fclean all

.PHONY: all libft printf clean fclean re
