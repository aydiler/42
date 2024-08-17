# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adiler <adiler@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 12:44:41 by adiler            #+#    #+#              #
#    Updated: 2023/12/22 17:35:07 by adiler           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFTDIR = ./libft
LIBFTNAME = libft.a
PRINTFNAME = printf.a

SRCS = $(wildcard *.c)

OBJS=$(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = cc

all: $(NAME)

$(NAME): $(LIBFTNAME) $(PRINTFNAME)
	ar rc $(NAME) $(OBJS) *.o libft/*.o

$(LIBFTNAME):
	make -C $(LIBFTDIR) all

$(PRINTFNAME):$(OBJS)
	ar rc $(PRINTFNAME) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(OBJS)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
