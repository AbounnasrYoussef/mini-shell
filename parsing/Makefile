NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = mini.c\
      $(wildcard utils/*.c) \
      $(wildcard syntaxe_errors/*.c) \
	  $(wildcard ft_malloc/*.c)\
	  $(wildcard tokens/*.c)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -lreadline

$(OBJ): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

print:
	@echo $(SRC)
