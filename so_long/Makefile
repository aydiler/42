NAME		= so_long

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBS		= -L./includes/minilibx-linux -lmlx -lXext -lX11 \
			  -L./includes/libft -lft \
			  -L./includes/printf -lprintf \
			  -L./includes/get_next_line -lgnl

INCLUDES	= -I./includes \
			  -I./includes/libft \
			  -I./includes/printf \
			  -I./includes/get_next_line \
			  -I./includes/minilibx-linux

SOURCE		= ./source/

MAP = $(addprefix 0-map/, \
	0_map.c 1_map_validation.c 2_map_update.c 3_map_utils.c \
	4_map_render_player.c \
)

WINDOW = $(addprefix 1-window/, \
	0_window.c 1_screen_validations.c \
)

MOVE = $(addprefix 2-movements/, \
	mov_left.c mov_right.c mov_up.c mov_down.c mov_utils.c \
)

SRC = $(addprefix $(SOURCE), \
	$(MOVE) $(MAP) $(WINDOW) \
	0_endgame.c 1_images.c \
	so_long.c \
)

OBJ = $(SRC:%.c=%.o)

all: libft printf gnl $(NAME)

libft:
	make -C ./includes/libft

printf:
	make -C ./includes/printf

gnl:
	make -C ./includes/get_next_line

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $(<:%.c=%.o)

$(NAME): $(OBJ)
	make -C ./includes/minilibx-linux
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
