/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:59:18 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/02 17:19:15 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_list_env* ft_supp_arg(t_list_env *list_env, char *arg)
{
	t_list_env *tmp_node;
	t_list_env *tmp_list;
	int i;
	
	tmp_node = NULL;
	tmp_list = list_env;
	i = 0;
	while ((list_env) != NULL)
	{
		if (ft_strcmpp((list_env)->variable, arg) == 0)
		{
			if(i == 0)
			{
				list_env = list_env->next;
				return list_env;
			}
			else
			{
				if (tmp_node)
					tmp_node->next = list_env->next;
				else 
				{
					tmp_list = list_env->next;
				}
				break;
			}
			
		}
		i++;
		tmp_node = list_env;
		(list_env) = (list_env)->next;
	}
	return (tmp_list);
}

void ft_unset(t_list_env *list_env, char **args)
{
	int i;
	int j;
	
	i = 1;
	j = 0;
	while (args[i] != NULL)
	{
		while(args[i][j] != '\0')
		{
			if (!(args[i][j] == '_' || (args[i][j] >= 'a' && args[i][j] <= 'z')
				|| (args[i][j] >= 'A' && args[i][j] <= 'Z')
				|| (args[i][j] >= '0' && args[i][j] <= '9')) 
				|| (args[i][0] >= '0' && args[i][0] <= '9'))
				{
					write(2, "unset: `", 8);
					write(2, args[i], strlen(args[i]));
					write(2, ": not a valid identifier\n", 25);
					break;
				}
			j++;
		}
		list_env = ft_supp_arg(list_env, args[i]);
		j = 0;
		i++;
	}
}
