##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile to compil the -lmy
##

SRC		=	main.c			\
			setting_up.c

OBJ 	= 	$(SRC:.c=.o)

TEST 	=	tests/test_error_generating.c

NAME	= 	setting_up

TESTER	= 	unit_tests

CFLAGS =	-I ./include -Wall -Wshadow -Wextra

LDFLAGS 	=	-L ./lib/my -lmy

CC 		=	 gcc

all:	$(NAME)

./lib/my/libmy.a:
		$(MAKE) -C ./lib/my
		cp ./lib/my/my.h ./include

$(NAME): ./lib/my/libmy.a $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)
		@echo -e "\e[1;36m{ Binary ready !! }\e[00;37m"

unit_tests: fclean all
	@$(CC) -o $(TESTER) $(OBJ) $(CFLAGS) $(LDFLAGS) $(TEST)	\
	--coverage -lcriterion
	clear

tests_run: unit_tests
	@./$(TESTER)

clean:
		$(RM) *.gc* $(OBJ)
		$(MAKE) clean -C ./lib/my
		@echo -e "\e[1;33m[ Useless files have been deleted ]\e[00;37m"

fclean: clean
		$(RM) $(NAME) $(TESTER) ./include/my.h
		$(MAKE) fclean -C ./lib/my
		@echo -e "\e[1;33m[ Binary has been deleted ]\e[00;37m"

re: fclean all
