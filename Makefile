NAME = minishell
CC = cc
CFLAGS =  -Wall -Wextra -Werror
PARS = parsing
SRC = minishell.c  signals.c\
		$(PARS)/syntaxe_errors/syntaxe_errors.c\
		$(PARS)/syntaxe_errors/error_pipe.c\
		$(PARS)/syntaxe_errors/error_quote.c\
		$(PARS)/syntaxe_errors/error_redi.c\
		$(PARS)/tokens/tokens.c\
		$(PARS)/tokens/handel_world.c\
		$(PARS)/tokens/handel.c\
		$(PARS)/tokens/utils.c\
		$(PARS)/utils/ft_isalnum.c\
		$(PARS)/utils/ft_isalpha.c\
		$(PARS)/utils/ft_itoa.c\
		$(PARS)/utils/ft_memcpy.c\
		$(PARS)/utils/ft_split.c\
		$(PARS)/utils/ft_strchr.c\
		$(PARS)/utils/ft_strcmp.c\
		$(PARS)/utils/ft_strdup.c\
		$(PARS)/utils/ft_strjoin.c\
		$(PARS)/utils/ft_strlen.c\
		$(PARS)/utils/ft_strtrim.c\
		$(PARS)/utils/ft_substr.c\
		$(PARS)/utils/skip_space.c\
		$(PARS)/ft_malloc/ft_malloc.c\
		$(PARS)/expanding/dollar.c\
		$(PARS)/expanding/double_quote.c\
		$(PARS)/expanding/expand_token.c\
		$(PARS)/expanding/expand.c\
		$(PARS)/expanding/single_quote.c\
		$(PARS)/expanding/split_tokens.c\
		$(PARS)/expanding/utils.c\
		$(PARS)/struct_atmane/cmd_token.c\
		$(PARS)/struct_atmane/free_list.c\
		$(PARS)/struct_atmane/redir_token.c\
		$(PARS)/struct_atmane/struct_at.c\
		$(PARS)/here_doc/here.c\
		$(PARS)/here_doc/utils_here.c\
		execution/built-in/cd.c\
		execution/built-in/echo.c\
		execution/built-in/env.c\
		execution/built-in/exit.c\
		execution/built-in/main.c\
		execution/built-in/pwd.c\
		execution/built-in/unset.c\
		execution/utils/ft_memcpy.c\
		execution/built-in/export_suit.c\
		execution/built-in/export.c\
		execution/utils/ft_split.c\
		execution/utils/utili_1.c\
		execution/pipe/pipe.c\
		execution/pipe/cherche_path.c\
		execution/pipe/ft_redirections.c\
		execution/pipe/utils_pipe.c\


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ) -o $(NAME) -lreadline -L/mnt/homes/yabounna/.brew/opt/readline/lib

$(OBJ): %.o : %.c minishell.h
	$(CC) $(CFLAGS) -c -I/mnt/homes/yabounna/.brew/opt/readline/include $< -o $@

clean: 
	rm -f $(OBJ)


fclean: clean
	rm -f $(NAME)

re: fclean all
