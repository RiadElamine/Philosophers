# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: relamine <relamine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 10:34:16 by relamine          #+#    #+#              #
#    Updated: 2024/09/15 19:23:32 by relamine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = philo

SOURCES =	Mandatory/main.c \
			Mandatory/parser.c \
			Mandatory/philo.c \
			Mandatory/utils.c \
			Mandatory/monitor.c \

SRC_OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-g #-fsanitize=thread #-fsanitize=address
RM =rm -f

Mandatory/%.o: Mandatory/%.c Mandatory/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(SRC_OBJECTS)
	$(CC) $(CFLAGS) $(SRC_OBJECTS) -o $(NAME) 	

clean:
	$(RM) $(SRC_OBJECTS) 

fclean: clean
	$(RM) $(NAME) 

re: fclean all 
