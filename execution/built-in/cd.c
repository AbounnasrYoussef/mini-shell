/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:24:19 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/15 15:06:57 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_update_opwd(t_list **env)
{
	while (*env != NULL)
	{
		if (ft_strcmp((*env)->variable, "OLDPWD") == 0)
		{
			(*env)->valeur_vari = ft_pwd();
		}
		*env = (*env)->next;
	}
}

char *ft_cherch_home(t_list *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->variable, "HOME") == 0)
			return (env->valeur_vari);
		env = env->next;
	}
	return NULL;
}

int check_home(t_list *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->variable, "HOME") == 0)
			return (1);
		env = env->next;
	}
	return 0;
}

void ft_cd(char **args, char *line, t_list *env)
{
	int	a;
	int len_args;

	//ft_update_opwd(&env);
	len_args = ft_strlen_argc(args);
	if (len_args == 1)
	{
		if (check_home(env) == 0)
			printf ("cd: HOME not set\n");
		else
			a = chdir(ft_cherch_home(env));
	}
	else if (access( args[1], F_OK) == 0)
	{
		a = chdir(args[1]);
	}
	else
		printf("No such file or directory\n");
	return ;
}
