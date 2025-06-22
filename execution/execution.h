/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:19:57 by arahhab           #+#    #+#             */
/*   Updated: 2025/06/22 18:07:27 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_list
{
	void	*ligne;
	void	*variable;
	void 	*valeur_vari;
	struct s_list	*next;
}	t_list;

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void ft_put_string(char *str);
int	ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
t_list *ft_env(char **str);
#endif