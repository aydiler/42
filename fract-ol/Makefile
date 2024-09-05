NAME		= fractol
BONUS_NAME	= fractol_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBS		= -L./includes/minilibx-linux -lmlx -lXext -lX11 \
			  -L./includes/printf -lprintf \
			  -L./includes/libft -lft \
			  -lm

INCLUDES	= -I./includes \
			  -I./includes/libft \
			  -I./includes/printf \
			  -I./includes/minilibx-linux

SOURCE		= ./source/

SRC = $(addprefix $(SOURCE), \
    fractol.c fractol_utils.c hooks.c parse_arguments.c ft_atof.c\
)

BONUS_SRC = $(addprefix $(SOURCE), \
    fractol_bonus.c fractol_utils_bonus.c hooks_bonus.c parse_arguments_bonus.c ft_atof.c \
)

OBJ = $(SRC:%.c=%.o)
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

DEPS = includes/fractol.h
BONUS_DEPS = includes/fractol_bonus.h

all: libft printf minilibx $(NAME)

bonus: libft printf minilibx $(BONUS_NAME)

libft:
	make -C ./includes/libft

printf:
	make -C ./includes/printf

minilibx:
	make -C ./includes/minilibx-linux

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $(<:%.c=%.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBS) -o $(BONUS_NAME)

clean:
	rm -rf $(OBJ) $(BONUS_OBJ)
	rm -rf ./a.out
	make clean -C ./includes/libft
	make clean -C ./includes/printf
	make clean -C ./includes/minilibx-linux

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)
	make fclean -C ./includes/libft
	make fclean -C ./includes/printf

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus libft printf clean fclean re re_bonus