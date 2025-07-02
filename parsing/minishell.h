/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:35:05 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/26 17:16:40 by yabounna         ###   ########.fr       */
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
    struct y_token *next;
}   t_token;

typedef struct garbage
{
    void *ptr; // hada pointer generique vers n'importe quelle memoire allouee 
    struct garbage *next;  // hada next l prochaine element dial dik la list
}   garbage;

typedef struct s_list
{
	void	*ligne;
	void	*variable;
	void 	*valeur_vari;
	struct s_list	*next;
}	t_list;



//tokenisation
t_token *tokens(char *line,garbage **garb);
void handle_word(const char *line, int *i, t_token **tokens , garbage **garb);
void handle_single_operator(char *line, int *i, t_token **tokens , garbage **garb);
void handel_double_operator(char *line ,int *i , t_token **tokens, garbage **garb);
void handel_quote(char *line , int  *i , t_token **token ,garbage **garb);
type_token get_token_type(char *str);
t_token *new_token(char *value, type_token type,garbage **garb);
void add_token(t_token **list, t_token *new_tok);
void space_skip(char *line , int *i);


// syntaxe errors
int syntaxe_errors(char *args);
int error_pipe(char *caracter , int *i);
int error_redir(char *caracter , int *i);
int error_quote(char *caracter, int *i);


// utils
int	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int skip_space(char c);
int is_quote(char c);
char	*ft_substr(char const *s, unsigned int start, size_t len,garbage **garb);
char	*ft_strdup(const char *s1,garbage **garb);
int is_operator(char c);
char	*ft_strjoin(char const *s1, char const *s2, garbage **garb);


#endif