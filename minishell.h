/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:29:59 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 15:13:15 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "parsing/ft_malloc/ft_malloc.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

extern int g_exit_status;
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


typedef struct s_garbage
{
    void *ptr; // hada pointer generique vers n'importe quelle memoire allouee 
    struct s_garbage *next;  // hada next l prochaine element dial dik la list
}   t_garbage;


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
	t_garbage	**garb;
}	t_expand_ctx;

typedef struct s_quote_ctx
{
	char		**res;
	int			*quoted_flag;
	t_garbage	**garb;
}	t_quote_ctx;



// syntaxe_error
int syntaxe_errors(char *args);
int	error_quote(char *caracter, int *i);
int	error_pipe(char *caracter, int *i);
int	error_redir(char *str, int *i);





//tokens
t_token *tokens(const char *line, t_garbage **garb);
void handel_quote(const char *line , int  *i , t_token **token ,t_garbage **garb);
void handel_double_operator(const char *line ,int *i , t_token **tokens, t_garbage **garb);
void handle_single_operator(const char *line, int *i, t_token **tokens , t_garbage **garb);
void handle_word(const char *line, int *i, t_token **tokens, t_garbage **garb);
//tokens//utils
void add_token(t_token **list, t_token *new_tok);
t_token	*new_token_0(char *value, type_token type, t_garbage **garb);
type_token get_token_type(char *str);
t_token	*new_token(char *value, type_token type,int i, t_garbage **garb);



//expanding
void expand_all_tokens(t_token **tokens, int exit_code, t_list_env *env, t_garbage **garb);
char	*expand_token(char *value, int exit_code, t_list_env *env, t_garbage **garb);
char	*expand_dollar(char *value, int *i, int exit_code, t_list_env *env, t_garbage **garb);
void	append_double_quote(const char *val, int *i, char **res, t_expand_ctx ctx);
void	append_single_quote(const char *val, int *i, char **res, t_garbage **garb);
char	*get_env_value(char *name, t_list_env *env, t_garbage **garb);
void	replace_token(t_token **head, t_token *old, t_token *new_list);
t_token	*get_last_token(t_token *tokens);
t_token	*split_into_tokens(char *str, t_garbage **garb);
void	add_token_back(t_token **head, t_token *new_token);
t_token	*new_token_0(char *value, type_token type, t_garbage **garb);
int ft_exit_status(int status, int flag);
int	is_valid_var_char(char c);
char	*ft_strtrim_custom(char *str, t_garbage **garb, int quoted);


//struct_atmane
char **extract_cmd_from_tokens(t_token *tokens, t_garbage **garb);
void free_exec_list(t_exec *exec_list);
int	is_redirection(type_token type);
t_file	*extract_redirs_from_tokens(t_token *tokens, t_garbage **garb);
t_exec	*parse_tokens_to_exec_list(t_token *tokens, t_garbage **garb);

//utils
int     ft_isalnum(int c);
int     ft_isalpha(int c);
char    *ft_itoa(int n, t_garbage **garb);
void    *ft_memcpy(void *dst, const void *src, size_t n);
char    **ft_split(const char *s, char c, t_garbage **garb);
char    *ft_strchr(const char *s, int c);
int     ft_strcmp(const char *s1, const char *s2);
char    *ft_strdup(const char *s1, t_garbage **garb);
char    *ft_strjoin(char const *s1, char const *s2, t_garbage **garb);
char    *ft_strtrim(char const *s1, char const *set, t_garbage **garb);
char    *ft_substr(char const *s, unsigned int start, size_t len, t_garbage **garb);
int     skip_space(char c);
int     is_quote(char c);
int     is_operator(char c);
int     redirection(char c);
void    space_skip(const char *line , int *i);
size_t  ft_strlen(const char *s);



//env
t_list_env *ft_env(char **str);
void	ft_lstadd_back(t_list_env **lst, t_list_env *new);
t_list_env	*ft_lstnew(void *variable, void *valeur_vari, void *ligne);
char	**i_split(char const *s, char c);

//signals 
void	setup_signals(void);
void	handle_sigquit(int sig);
void	handle_sigint(int sig);


//heredoc
void process_heredocs(t_exec *exec, t_list_env *env, t_garbage **garb);


#endif