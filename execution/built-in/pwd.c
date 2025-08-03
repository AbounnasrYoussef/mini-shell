/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:49:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/03 14:49:00 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int check_exist_PWD(t_list_env *env)
{
	t_list_env *copy_env;
	copy_env = env;
	while(copy_env)
	{
		if (ft_strcmpp(copy_env->variable, "PWD") == 0)
		{
			return 0;
		}
		copy_env = copy_env->next; 
	}
	return 1;
}

char *ft_pwd(t_list_env *env)
{
	char *buffer;
	t_list_env *copy_env;
	int check_pwd;

	copy_env = env;
	buffer = NULL;
	check_pwd = check_exist_PWD(env);
	while (env != NULL)
	{
		if(check_pwd == 0)
		{
			if (ft_strcmpp(env->variable, "PWD") == 0)
			{
				buffer = env->valeur_vari;
			}
		}
		else if(ft_strcmpp(env->variable, "PO") == 0)
		{
			ft_lstadd_backk(&env, ft_lstneww("PWD", env->valeur_vari, ""));
			buffer = env->valeur_vari;
		}
		env = env->next;
	}
	if (getcwd(NULL, 0) != NULL)
		buffer = getcwd(NULL, 0);
	return buffer;
}
