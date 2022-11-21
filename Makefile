# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 14:06:13 by zyunusov          #+#    #+#              #
#    Updated: 2022/11/21 11:21:57 by zyunusov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

SRCS = main.c data_init.c philo_init.c philo_utils.c death_check.c

OBJ = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	$(RM) ./*.o 

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re