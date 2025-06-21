/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:35:05 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/21 11:09:47 by yabounna         ###   ########.fr       */
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






//tokenisation
void tokens(char *line);

// syntaxe errors
void printf_error(int x);
void syntaxe_errors(char *args);
int error_pipe(char *caracter , int *i);
int error_redir(char *caracter , int *i);
int error_quote(char *caracter, int *i);


// utils
int	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int skip_space(char c);



#endif