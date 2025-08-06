/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:12:25 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/06 16:48:52 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_count_env(t_list_env *env)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (env != NULL)
	{
		if (env->valeur_vari != NULL)
		{
			c++;
		}
		env = env->next;
		i++;
	}
	return c;
}

char **tab_env(t_list_env *env, t_garbage **garb)
{
	t_list_env *copy_env;
	char **tab_env;
	int i;
	
	tab_env = NULL;
	tab_env = ft_malloc(garb, sizeof(char *) * (ft_count_env(env) + 1));
	copy_env = env;
	i = 0;
	while(copy_env != NULL)
	{
		if (copy_env->valeur_vari != NULL)
		{
			tab_env[i] = ft_concat(copy_env->variable, "=", garb);
			tab_env[i] = ft_concat(tab_env[i], copy_env->valeur_vari, garb);
			i++;
		}
		copy_env = copy_env->next;
	}
	tab_env[i] = NULL;
	return tab_env;
}

int is_slash(char *str)
{
	int i;
	i = 0;
	while(str && str[i] != '\0')
	{
		if (str[i] == '/')
		{
			return 0;
		}
		i++;
	}
	return 1;
}

int count_cmd(t_exec *data)
{
	int i;
	i = 0;

	while(data != NULL)
	{
		data = data->next;
		i++;
	}
	return i; 
}

int is_built_in(char *str)
{
	if(ft_strcmpp(str, "export") == 0)
		return 0;
	else if(ft_strcmpp(str, "cd") == 0)
		return 0;
	else if(ft_strcmpp(str, "echo") == 0)
		return 0;
	else if(ft_strcmpp(str, "env") == 0)
		return 0;
	else if(ft_strcmpp(str, "exit") == 0)
		return 0;
	else if(ft_strcmpp(str, "pwd") == 0)
		return 0;
	else if(ft_strcmpp(str, "unset") == 0)
		return 0;
	return -1;
}
