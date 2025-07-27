/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:19:57 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/27 13:29:51 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

//typedef struct s_list_env
//{
//	void	*ligne;
//	void	*variable;
//	void 	*valeur_vari;
//	struct s_list_env	*next;
//}	t_list_env;

#include "../parsing/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void ft_put_string(char *str);
int	ft_strcmpp(const char *s1, const char *s2);
char	**ft_splitt(char const *s, char c);
void	*ft_memcpyy(void *dst, const void *src, size_t n);
t_list_env *ft_envvv(char **str);
int ft_strlen_argc(char **str);
int ft_strlenn(char *str);
void ft_cd(char **args, t_list_env *env);
void ft_echo(int argc, char **str);
void ft_exit (int len, char **str);
void	ft_lstadd_backk(t_list_env **lst, t_list_env *new);
t_list_env	*ft_lstneww(void *variable, void *valeur_vari, void *ligne);
t_list_env *ex_sort(t_list_env *list_env);
void ft_print_env(t_list_env *env);
void ft_export(t_list_env *list_env, char **args);
char *ft_pwd(t_list_env *env);
void ft_unset(t_list_env *list_env, char **args);
void ft_print_env_ex(t_list_env *env);
t_list_env* ft_supp_arg(t_list_env *list_env, char *arg);
char *ft_concat(char *str, char *str2);
char *cherche_path_cmd(char *cmd, t_list_env *env);
int ft_built_in(int argc, t_exec *data, t_list_env *env);
t_list_env *supp_var_nv(t_list_env *env);
void ft_print_env(t_list_env *env);
void ft_print_env_ex(t_list_env *env);
void ft_pipe(int argc, t_exec *data, t_list_env *env);
#endif