NAME		=	so_long

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

MLX			=	-L ./minilibx-linux -lmlx -lXext -lX11

LIB_FLAGS	=	-L ./libft -lft

INCLUDE		=	-I ./includes

SOURCE		=	./source/

MAP =		$(addprefix 0-map/, \
		0_map.c 1_map_validation.c 2_map_update.c 3_map_utils.c \
		4_map_render_player.c \
)

WINDOW =	$(addprefix 1-window/, \
		0_window.c 1_screen_validations.c \
)

MOVE =		$(addprefix 2-movements/, \
		mov_left.c mov_right.c mov_up.c mov_down.c mov_utils.c \
)

SRC =         $(addprefix $(SOURCE), \
                $(MOVE) $(MAP) $(WINDOW) \
                0_endgame.c 1_images.c \
                so_long.c get_next_line.c \
				get_next_line_utils.c \
)

OBJ = $(SRC:%.c=%.o)

all: $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -g -c $< -o $(<:%.c=%.o)

$(NAME): $(OBJ)
	rm -rf $(NAME)
	make all -C ./libft
	make all -C ./minilibx-linux
	$(CC) $(CFLAGS) $(OBJ) $(LIB_FLAGS) $(MLX) -o $(NAME)

clean:
	rm -rf $(OBJ) $(OBJ_B)
	rm -rf ./a.out
	make clean -C ./libft

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)
	make fclean -C ./libft

re: fclean all

.PHONY: all bonus clean fclean re
