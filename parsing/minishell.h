/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:35:05 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 11:49:39 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H



#include "ft_malloc/ft_malloc.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

// enumeration pour reconnaitre chaque type

typedef enum type_token{
    WORD,
    PIPE,
    RDR_IN,
    RDR_OUT,
    APPEND,
    HERE_DOC,
}   type_token;

// linked_list pour  token 
// hadi bach nstokiwe kola element 
typedef struct y_token{
    char *value;
    type_token type;
	int quoted;
	int double_quote;
	int join;
    struct y_token *next;
}   t_token;

typedef struct s_file
{
	int				type;
	char			*file_name;
	struct s_file	*next;
}	t_file;

typedef struct s_exec
{
	char			**cmd;
	t_file			*files;
	struct s_exec	*next;
}	t_exec;


typedef struct garbage
{
    void *ptr; // hada pointer generique vers n'importe quelle memoire allouee 
    struct garbage *next;  // hada next l prochaine element dial dik la list
}   garbage;


typedef struct s_list_env
{
	void	*ligne;
	void	*variable;
	void 	*valeur_vari;
	struct s_list_env	*next;
}	t_list_env;

// hadi 3la 9bol expanding
typedef struct s_expand_ctx
{
	t_list_env	*env;
	int			exit_code;
	garbage	**garb;
}	t_expand_ctx;


//tokenisation
t_token *tokens(char *line,garbage **garb);
void handle_word(const char *line, int *i, t_token **tokens , garbage **garb);
void handle_single_operator(char *line, int *i, t_token **tokens , garbage **garb);
void handel_double_operator(char *line ,int *i , t_token **tokens, garbage **garb);
void handel_quote(char *line , int  *i , t_token **token ,garbage **garb);
type_token get_token_type(char *str);
t_token	*new_token(char *value, type_token type,int i, garbage **garb);
void add_token(t_token **list, t_token *new_tok);
void space_skip(char *line , int *i);
void	add_token_back(t_token **head, t_token *new_token);
char	**i_split(char const *s, char c);
int printf_error();
t_token	*new_token_0(char *value, type_token type, garbage **garb);


// expand
void	expand_all_tokens(t_token **tokens, int exit_code,t_list_env *env, garbage **garb);
char	*expand_token(char *value, int exit_code,t_list_env *env, garbage **garb);
void	append_single_quote(const char *val, int *i, char **res,garbage **garb);
void	append_double_quote(const char *val, int *i, char **res,t_expand_ctx ctx);
char	*expand_dollar(char *value, int *i, int exit_code,t_list_env *env, garbage **garb);
void	replace_token(t_token **head, t_token *old, t_token *new_list);
t_token	*get_last_token(t_token *tokens);
t_token	*split_into_tokens(char *str, garbage **garb);
char *ft_strtrim_custom(char *str, garbage **garb, int quoted);
int	is_valid_var_char(char c);
char	*ft_strtrim_custom(char *str, garbage **garb, int quoted);
char	*get_env_value(char *name, t_list_env *env, garbage **garb);
int ft_exit_status(int status, int flag);


// syntaxe errors
int syntaxe_errors(char *args);
int error_pipe(char *caracter , int *i);
int error_redir(char *caracter , int *i);
int error_quote(char *caracter, int *i);


// utils
int	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	**ft_split(const char *s, char c, garbage **garb);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int skip_space(char c);
int is_quote(char c);
char	*ft_substr(char const *s, unsigned int start, size_t len,garbage **garb);
char	*ft_strdup(const char *s1,garbage **garb);
int is_operator(char c);
char	*ft_strjoin(char const *s1, char const *s2, garbage **garb);
char	*ft_strchr(const char *s, int c);
int	ft_isalnum(int c);
char	*ft_itoa(int n, garbage **garb);
int	ft_isalpha(int c);
char	*ft_strtrim(char const *s1, char const *set, garbage **garb);
t_list_env *ft_env(char **str);


// strcut atmane
// void	expand_all_tokens(t_token **tokens, int exit_code,t_list_env *env, garbage **garb);
t_exec	*parse_tokens_to_exec_list(t_token *tokens, garbage **garb);
char	**extract_cmd_from_tokens(t_token *tokens, garbage **garb);
t_file	*extract_redirs_from_tokens(t_token *tokens, garbage **garb);
void free_exec_list(t_exec *exec_list);
int	is_redirection(type_token type);

///////
char    *get_next_line(int fd);

#endif