NAME = philo

SRC = main.c init.c threads.c utils.c monitor.c philo.c parse.c

MANPATH = $(addprefix ./source/, $(SRC))
OBJ = $(SRC:.c=.o)
OBJPATH = $(addprefix ./source/, $(OBJ))

FLAGS = -Wall -Wextra -Werror

HEADER = ./includes/philo.h

.PHONY: all clean fclean re debug tsan

all: $(NAME)

$(NAME): $(OBJPATH)
	@cc $(FLAGS) -o $(NAME) $(OBJPATH)

./source/%.o: ./source/%.c $(HEADER)
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJPATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

tsan: FLAGS += -pthread -g
tsan: re