/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:19:57 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/06 20:26:19 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "../minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

typedef struct s_list_env  t_list_env;
typedef struct s_exec  t_exec;
typedef struct s_garbage	t_garbage;

void		ft_put_string(char *str);
int			ft_strcmpp(const char *s1, const char *s2);
char		**ft_splitt(char const *s, char c, t_garbage **garb);
void		*ft_memcpyy(void *dst, const void *src, size_t n);
t_list_env	*ft_envvv(char **str, t_garbage **garb);
int			ft_strlen_argc(char **str);
int			ft_strlenn(char *str);
void		ft_cd(char **args, t_list_env *env, int *status);
void		ft_echo(char **str);
void		ft_exit (int argc, int len, char **str, t_garbage **garb, int *status);
void		ft_lstadd_backk(t_list_env **lst, t_list_env *new);
t_list_env	*ft_lstneww(void *variable, void *valeur_vari, t_garbage **garb);
t_list_env	*ex_sort(t_list_env *list_env);
void		ft_print_env(t_list_env *env);
void		ft_export(t_list_env *list_env, char **args, t_garbage **garb, int *status);
char		*ft_pwd(t_list_env *env);
void		ft_unset(t_list_env **list_env, char **args, int *status);
void		ft_print_env_ex(t_list_env *env);
void		ft_supp_arg(t_list_env **list_env, char *arg);
char		*ft_concat(char *str, char *str2, t_garbage **garb);
char		*cherche_path_cmd(char *cmd, t_list_env **env, t_exec *data, int count_cmd, t_garbage **garb, int *status);
int			ft_built_in(t_exec *data, t_list_env **env, int count_cmd, t_garbage **garb, int *status);
void		ft_print_env(t_list_env *env);
void		ft_print_env_ex(t_list_env *env);
void		ft_pipe(t_exec *data, t_list_env **env, t_garbage **garb);
char		*ft_cherch_home(t_list_env *env);
int			verif_exist(t_list_env **list_env, char *arg);
void		repmlacer_elem(t_list_env **list_env, char *var, char *arg, int d, t_garbage **garb);
void		ajout_exp_elem_help(t_list_env **list_env, char *args, int i, int c, int d, char **arg_varia, t_garbage **garb);
void		ajout_exp_elem(t_list_env **list_env, char *args, int i, int j, t_garbage **garb);
void		error_export(char **args, int i, int *status);
void		ft_redirection(t_exec *data, t_garbage **garb);
int			ft_count_env(t_list_env *env);
char		**tab_env(t_list_env *env, t_garbage **garb);
int			is_slash(char *str);
int			count_cmd(t_exec *data);
int			is_built_in(char *str);
int			is_espace_tabulion(char *cmd);
int			ft_count_cmd(t_exec *data);
unsigned long long	ft_atoi(int len, char *nbr, int count_cmd, t_garbage **garb);
#endif