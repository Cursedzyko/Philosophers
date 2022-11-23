# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 14:06:13 by zyunusov          #+#    #+#              #
#    Updated: 2022/11/23 14:14:20 by zyunusov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

SRCS = main.c philo_utils.c philo.c routine_utils.c \
		routine.c time.c atoi.c malloc_check.c

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