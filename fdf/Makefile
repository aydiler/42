NAME		=fdf

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBS		= -L./includes/minilibx-linux -lmlx -lXext -lX11 \
			  -L./includes/libft -lft \
			  -L./includes/printf -lprintf \
			  -L./includes/get_next_line -lgnl \
			  -lm

INCLUDES	= -I./includes \
			  -I./includes/libft \
			  -I./includes/printf \
			  -I./includes/get_next_line \
			  -I./includes/minilibx-linux

SOURCE		= ./source/

SRC = $(addprefix $(SOURCE), \
    fdf.c \
)

OBJ = $(SRC:%.c=%.o)

all: libft printf gnl minilibx $(NAME)

libft:
	make -C ./includes/libft

printf:
	make -C ./includes/printf

gnl:
	make -C ./includes/get_next_line

minilibx:
	make -C ./includes/minilibx-linux

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $(<:%.c=%.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

clean:
	rm -rf $(OBJ)
	rm -rf ./a.out
	make clean -C ./includes/libft
	make clean -C ./includes/printf
	make clean -C ./includes/get_next_line
	make clean -C ./includes/minilibx-linux

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./includes/libft
	make fclean -C ./includes/printf
	make fclean -C ./includes/get_next_line

re: fclean all

.PHONY: all libft printf gnl clean fclean re
