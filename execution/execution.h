/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:19:57 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/17 05:55:49 by arahhab          ###   ########.fr       */
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
int ft_strlen_argc(char **str);
int ft_strlen(char *str);
void ft_cd(char **args, char *line, t_list *env);
void ft_echo(int argc, char **str);
void ft_exit (int len, int argc, char **str);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *variable, void *valeur_vari, void *ligne);
t_list *ex_sort(t_list *list_env);
void ft_print_env(t_list *env);
void ft_export(t_list *list_env, char **args, int argc);
char *ft_pwd(void);
void ft_unset(t_list *list_env, char **args);
void ft_print_env_ex(t_list *env);
t_list* ft_supp_arg(t_list *list_env, char *arg);
char *ft_concat(char *str, char *str2);
char *cherche_path_cmd(char *cmd, char **env);
char *ft_concat(char *str, char *str2);
#endif