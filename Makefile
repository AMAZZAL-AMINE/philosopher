# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 14:01:18 by mamazzal          #+#    #+#              #
#    Updated: 2023/05/13 15:20:12 by mamazzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c ft_atoi.c error_msg.c get_philo_time.c print_actions.c \
	greate_sleep.c

OBJ = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all