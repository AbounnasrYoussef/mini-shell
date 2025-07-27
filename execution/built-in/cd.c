/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:24:19 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/27 10:52:10 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

//void ft_update_opwd(t_list_env **env)
//{
//	while (*env != NULL)
//	{
//		if (ft_strcmpp((*env)->variable, "OLDPWD") == 0)
//		{
//			(*env)->valeur_vari = ft_pwd();
//		}
//		*env = (*env)->next;
//	}
//}

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
void ft_cd(char **args, t_list_env *env)
{
	int	a;
	int len_args;
	char *old_pwd;
	char *new_pwd;
	
	old_pwd = NULL;
	new_pwd = NULL;
	len_args = ft_strlen_argc(args);
	if (len_args == 1)
	{
		if (check_home(env) == 0)
			printf ("cd: HOME not set\n");
		else
		{
			if (access(ft_cherch_home(env), F_OK) == 0)
			{
				old_pwd = getcwd(NULL, 0);
				a = chdir(ft_cherch_home(env));
				new_pwd = getcwd(NULL, 0);
				if (new_pwd == NULL)
					printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
				ft_r_pwd_oldp(env, new_pwd, old_pwd);
			}
			else
				printf("cd: %s: No such file or directory\n", ft_cherch_home(env));

		}
	}
	else if (access( args[1], F_OK) == 0)
	{
		
		old_pwd = getcwd(NULL, 0);
		a = chdir(args[1]);
		new_pwd = getcwd(NULL, 0);
		if (new_pwd == NULL)
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		ft_r_pwd_oldp(env, new_pwd, old_pwd);
	}
	else
		printf("cd: %s: No such file or directory\n", args[1]);
	return ;
}
