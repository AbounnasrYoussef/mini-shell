/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:19:57 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/07 14:49:06 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_list_env	t_list_env;
typedef struct s_exec		t_exec;
typedef struct s_garbage	t_garbage;

typedef struct s_cd
{
	char	*old_pwd;
	char	*new_pwd;
}	t_cd;

typedef struct s_exit
{
	int	c_cmd;
	int	len;
	int	argc;
}	t_exit;

typedef struct s_export
{
	int	i;
	int	j;
	int	c;
}	t_export;

typedef struct s_info_pipe
{
	int			i;
	int			pid;
	int			fd[2];
	int			in_fd;
	char		*path_cmd;
	int			in_bultin;
	int			j;
	char		**tab_envv;
	struct stat	info;
}	t_info_pipe;

void		ft_put_string(char *str);
int			ft_strcmpp(const char *s1, const char *s2);
char		**ft_splitt(char const *s, char c, t_garbage **garb);
void		*ft_memcpyy(void *dst, const void *src, size_t n);
t_list_env	*ft_envvv(char **str, t_garbage **garb);
int			ft_strlen_argc(char **str);
int			ft_strlenn(char *str);
void		ft_cd(char **args, t_list_env *env);
void		ft_echo(char **str);
void		ft_exit(t_exit inf_exit, char **str, t_garbage **garb);
void		ft_lstadd_backk(t_list_env **lst, t_list_env *new);
t_list_env	*ft_lstneww(void *variable, void *valeur, t_garbage **garb);
t_list_env	*ex_sort(t_list_env *list_env, char *tmp);
void		ft_print_env(t_list_env *env);
void		ft_export(t_list_env *list_env, char **args, t_garbage **garb);
char		*ft_pwd(t_list_env *env);
void		ft_unset(t_list_env **list_env, char **args);
void		ft_print_env_ex(t_list_env *env);
void		ft_supp_arg(t_list_env **list_env, char *arg);
char		*ft_concat(char *str, char *str2, t_garbage **garb);
char		*cherch_path(char *cmd, t_list_env **env, t_exec *data, int count_cmd, t_garbage **garb);
int			ft_built_in(t_exec *data, t_list_env **env, int count_cmd, t_garbage **garb);
void		ft_print_env(t_list_env *env);
void		ft_print_env_ex(t_list_env *env);
void		ft_pipe(t_exec *data, t_list_env **env, t_garbage **garb);
char		*ft_cherch_home(t_list_env *env);
int			verif_exist(t_list_env **list_env, char *arg);
void		chng_el(t_list_env **list_env, char *var, char *arg, int d, t_garbage **garb);
void		exp_el_help(t_list_env **list_env, char *args, t_export indx, char **arg_varia, t_garbage **garb);
void		export_el(t_list_env **env, char *args, t_export indx, t_garbage **garb);
void		error_export(char **args, int i);
void		ft_redirection(t_exec *data, t_garbage **garb);
int			ft_count_env(t_list_env *env);
char		**tab_env(t_list_env *env, t_garbage **garb);
int			is_slash(char *str);
int			count_cmd(t_exec *data);
int			is_built_in(char *str);
int			is_espace_tabulion(char *cmd);
int			ft_count_cmd(t_exec *data);
#endif