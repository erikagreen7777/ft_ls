NAME = ft_ls

CC = gcc

FLAG += -Wall -Werror -Wextra -g 

SRC = srcs/main.c \
	srcs/list_dir.c \
	srcs/stat.c \
	srcs/recursion.c \
	srcs/switch.c \
	srcs/list_dir2.c \
	srcs/doubles.c \
	srcs/more.c \
	srcs/recuse.c \
	srcs/triples.c \
	srcs/rl.c \
	srcs/helpers.c \
	srcs/quadruples.c \
	srcs/ls_stat_helpers.c \
	srcs/morehelpers.c \
	srcs/helpersthree.c \
	srcs/lex_sorts.c \
	srcs/argparsing.c \
	srcs/maintwo.c \
	srcs/mainthree.c \
	srcs/mainfour.c \
	srcs/helpersfour.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a \

all: $(NAME)

$(NAME): $(OBJ)
	@make re -C libft
	@gcc $(FLAG) -o $(NAME) $(SRC) $(LIBFT) 
	@echo "\033[94mReady"

clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@echo "\033[34mCleaned"

fclean:
	@make clean
	@make fclean -C libft
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "\033[96mfCleaned"

re: fclean all
