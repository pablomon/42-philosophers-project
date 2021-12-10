CC		= gcc
FLAGS	= -Wall -Werror -Wextra -pthread

HEADER	= include/philo.h

SRC		= src/libft.c \
	src/main.c \
	src/misc.c \
	src/philos.c \
	src/utils.c

OBJ		= $(SRC:.c=.o)
NAME	= philo
GREEN	= \033[92;1m
NOCOLOR	= \033[0m # No Color

all :	$(NAME)

bonus:	$(NAME_BONUS)

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
