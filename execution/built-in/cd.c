/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:24:19 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/07 09:44:51 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_cherch_home(t_list_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "HOME") == 0)
			return (env->valeur_vari);
		env = env->next;
	}
	return (NULL);
}

int	check_home(t_list_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "HOME") == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_r_pwd_oldp(t_list_env *env, char *new_pwd, char *old_pwd)
{
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "PWD") == 0)
		{
			env->valeur_vari = new_pwd;
		}
		else if (ft_strcmpp(env->variable, "OLDPWD") == 0)
		{
			env->valeur_vari = old_pwd;
		}
		env = env->next;
	}
}

void	ft_error_cd(int index, char *arg_cd)
{
	if (index == 0)
	{
		write(2, "cd: error retrieving current directory:", 39);
		write(2, " getcwd: cannot access parent directories:", 42);
		write(2, " No such file or directory\n", 28);
	}
	if (index == 1)
	{
		write(2, "cd: ", 4);
		write(2, arg_cd, ft_strlenn(arg_cd));
		write(2, ": No such file or directory\n", 28);
	}
}

void	check_exec_fil(t_list_env *env, char *arg_cd, t_cd inf_pwd)
{
	int	a;

	a = 0;
	if (access(arg_cd, F_OK) == 0)
	{
		inf_pwd.old_pwd = getcwd(NULL, 0);
		a = chdir(arg_cd);
		if (a != 0)
			1 && (ft_error_cd(1, arg_cd), ft_exit_status(127, 1));
		inf_pwd.new_pwd = getcwd(NULL, 0);
		if (inf_pwd.new_pwd == NULL)
		{
			ft_error_cd(0, NULL);
			a = chdir("/");
			ft_exit_status(0, 1);
		}
		ft_r_pwd_oldp(env, inf_pwd.new_pwd, inf_pwd.old_pwd);
	}
	else
	{
		ft_error_cd(1, arg_cd);
		ft_exit_status(127, 1);
	}
}

void	ft_cd(char **args, t_list_env *env)
{
	int		len_args;
	t_cd	inf_pwd;

	inf_pwd.old_pwd = NULL;
	inf_pwd.new_pwd = NULL;
	len_args = ft_strlen_argc(args);
	if (len_args == 1)
	{
		if (check_home(env) == 0)
		{
			write(2, "cd: HOME not set\n", 17);
			ft_exit_status(1, 1);
		}
		else
			check_exec_fil(env, ft_cherch_home(env), inf_pwd);
	}
	else
		check_exec_fil(env, args[1], inf_pwd);
	return ;
}
