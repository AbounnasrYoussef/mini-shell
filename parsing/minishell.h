/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:35:05 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/18 13:41:59 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>



//tokenisation
void tokens(char *line);

// syntaxe errors
void printf_error(int x);
void syntaxe_errors(char *args);
void syntaxe_errors_pipe(char *args);
void syntaxe_errors_redi(char *args);


// utils
int	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif