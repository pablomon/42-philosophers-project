# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 11:33:58 by pmontese          #+#    #+#              #
#    Updated: 2021/11/24 11:37:15 by pmontese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
FLAGS	= -Wall -Werror -Wextra -pthread

HEADER	= include/philo_bonus.h

SRC		= src/libft.c \
	src/main_bonus.c \
	src/philos.c \
	src/utils.c
OBJ		= $(SRC:.c=.o)
NAME	= philo_bonus

GREEN	= \033[92;1m
NOCOLOR	= \033[0m # No Color

all :	$(NAME)

$(NAME) :	$(OBJ) $(HEADER)
	@echo "$(GREEN)\nBUILDING $(NAME)$(NOCOLOR)"
	$(CC) $(FLAGS) $(OBJ) -I $(HEADER) -o $(NAME)
	@echo "\n"

clean :
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean
