/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_suit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:42:24 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/31 21:45:45 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_isalnumm(int c)
{
	unsigned char	s;

	s = (unsigned char)c;
	if ((s >= '0' && s <= '9') || (s >= 'a' && s <= 'z')
		|| (s >= 'A' && s <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	ft_isalphaa(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

void check_args(t_list_env **list_env, char **args, int i, int j, int c)
{
	while (args[i] != NULL)
	{
		if (!(args[i][0] == '_' || ft_isalphaa(args[i][0])))
			(c = 1, error_export(args, i));
		while(args[i][j] != '\0' && args[i][j] != '=' && args[i][j] != '+')
		{
			if (!(args[i][j] == '_' || args[i][j] == '=' || ft_isalnumm(args[i][j])))
					(c = 1, error_export(args, i));
			j++;
		}
		if (args[i][j] == '+')
		{
			if (args[i][j+1] != '=')
				(c = 1, error_export(args, i));
			j++;
		}
		if (c == 0)
		{
			ajout_exp_elem(list_env, args[i], 0, 0);
		}
		else
			c = 0;
		j = 1;
		i++;
	}
}

t_list_env *ex_sort(t_list_env *list_env)
{
	t_list_env	*list1;
	char	*tmp;;
	t_list_env	*debut;
	
	list1 = list_env;
	debut = list1;
	while (list_env != NULL)
	{
		list1 = debut;
		while(list1 != NULL)
		{
			if (ft_strcmpp(list1->variable, (list_env->variable)) > 0)
			{
				tmp = list1->variable;
				list1->variable = list_env->variable;
				list_env->variable = tmp;
				
				tmp = list1->valeur_vari;
				list1->valeur_vari = list_env->valeur_vari;
				list_env->valeur_vari = tmp;
				
				list1 = debut;
			}
			list1 = list1->next;	
		}
		list_env = list_env->next;
	}
	return debut;
}

void ft_export(t_list_env *list_env, char **args)
{
	int c;
	c = ft_strlen_argc(args);
	if (c == 1)
	{
		ft_print_env_ex(ex_sort(list_env));
	}
	else
	{
		check_args(&list_env, args, 1, 1, 0);
	}
}
