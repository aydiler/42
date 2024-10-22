NAME = philo

SRC = main.c init.c threads.c utils.c monitor.c philo.c parse.c

MANPATH = $(addprefix ./source/, $(SRC))

FLAGS = -Wall -Wextra -Werror

HEADER = ./includes/philo.h

.PHONY: all clean fclean re debug tsan

all: $(NAME)

$(NAME): $(MANPATH) $(HEADER)
	@cc $(FLAGS) -o $(NAME) $(MANPATH)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

debug: FLAGS += -g
debug: re

tsan: FLAGS += -pthread -g
tsan: re