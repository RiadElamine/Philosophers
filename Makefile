# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: relamine <relamine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 10:34:16 by relamine          #+#    #+#              #
#    Updated: 2024/09/04 11:52:07 by relamine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = philo

SOURCES =  main.c \
			philo.c \
			parser.c

SRC_OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM =rm -f

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(SRC_OBJECTS)
	$(CC) $(CFLAGS) $(SRC_OBJECTS) -o $(NAME) 	

clean:
	$(RM) $(SRC_OBJECTS) 

fclean: clean
	$(RM) $(NAME) 
re: fclean all 
