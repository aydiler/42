NAME		= push_swap

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBS		= -L./includes/printf -lprintf \
			  -L./includes/libft -lft

INCLUDES	= -I./includes \
			  -I./includes/libft \
			  -I./includes/printf

SOURCE		= ./source/

MOVES = $(addprefix moves/, \
	push.c \
	rotate.c \
	reverse_rotate.c \
	swap.c \
)

SORTING = $(addprefix sorting/, \
	\
)

STACK = $(addprefix stack/, \
	build_stack.c declaration.c \
)

SRC = $(addprefix $(SOURCE), \
	$(MOVES) $(SORTING) $(STACK) \
	free_stack.c \
	push_swap.c \
	print_stacks.c \
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

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./includes/libft
	make fclean -C ./includes/printf

re: fclean all

.PHONY: all libft printf clean fclean re
