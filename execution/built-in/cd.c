/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:24:19 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/06 20:37:37 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char *ft_cherch_home(t_list_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "HOME") == 0)
			return (env->valeur_vari);
		env = env->next;
	}
	return NULL;
}

int check_home(t_list_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "HOME") == 0)
			return (1);
		env = env->next;
	}
	return 0;
}

void ft_r_pwd_oldp(t_list_env *env, char *new_pwd, char *old_pwd)
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

void check_exec_fil(t_list_env *env, char *arg_cd, char *old_pwd, char *new_pwd, int *status)
{
	int a;

	a = 0;
	
	if (access(arg_cd, F_OK) == 0)
	{
		old_pwd = getcwd(NULL, 0);
		a = chdir(arg_cd);
		if (a != 0)
		{
			write(2, "cd: ", 4);
			write(2, arg_cd, ft_strlenn(arg_cd));
			write(2, ": No such file or directory\n", 28);
			*status = 127;
			//exit(127);
		}
		new_pwd = getcwd(NULL, 0);
		if (new_pwd == NULL)
		{
			write(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 108);
			a = chdir("/");
			*status = 0;
			//exit(0);
		}
		ft_r_pwd_oldp(env, new_pwd, old_pwd);
	}
	else
	{
		write(2, "cd: ", 4);
		write(2, arg_cd, ft_strlenn(arg_cd));
		write(2, ": No such file or directory\n", 28);
		*status = 127;
		//exit(127);
	}
}

void ft_cd(char **args, t_list_env *env, int *status)
{
	int len_args;
	char *old_pwd;
	char *new_pwd;
	
	old_pwd = NULL;
	new_pwd = NULL;
	len_args = ft_strlen_argc(args);
	if (len_args == 1)
	{
		if (check_home(env) == 0)
		{
			write(2, "cd: HOME not set\n", 17);
			*status = 1;
			//exit(1);
		}
		else
			check_exec_fil(env, ft_cherch_home(env), old_pwd, new_pwd, status);
	}
	else
		check_exec_fil(env, args[1], old_pwd, new_pwd, status);
	return ;
}
