# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 00:03:44 by omadali           #+#    #+#              #
#    Updated: 2025/06/12 17:04:48 by omadali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c \
       srcs/init.c \
       srcs/monitor.c \
       srcs/philo_actions.c \
       srcs/philo_actions_utils.c \
       srcs/utils.c \
       srcs/philo_actions2.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
