/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_suit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:42:24 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/07 11:17:09 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_isalnumm(int c)
{
	unsigned char	s;

	s = (unsigned char)c;
	if ((s >= '0' && s <= '9') || (s >= 'a' && s <= 'z')
		|| (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isalphaa(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

void	check_args(t_list_env **env, t_export ix, char **args, t_garbage **garb)
{
	while (args[ix.i] != NULL)
	{
		if (!(args[ix.i][0] == '_' || ft_isalphaa(args[ix.i][0])))
			1 && (error_export(args, ix.i), ix.c = 1);
		while (args[ix.i][ix.j] != '\0' && args[ix.i][ix.j] != '='
			&& args[ix.i][ix.j] != '+')
		{
			if (!(args[ix.i][ix.j] == '_' || args[ix.i][ix.j] == '='
				|| ft_isalnumm(args[ix.i][ix.j])))
				1 && (error_export(args, ix.i), ix.c = 1);
			ix.j++;
		}
		if (args[ix.i][ix.j] == '+')
		{
			if (args[ix.i][ix.j + 1] != '=')
				1 && (error_export(args, ix.i), ix.c = 1);
			ix.j++;
		}
		if (ix.c == 0)
			export_el(env, args[ix.i], ix, garb);
		else
			ix.c = 0;
		ix.j = 1;
		ix.i++;
	}
}

t_list_env	*ex_sort(t_list_env *list_env, char *tmp)
{
	t_list_env	*list1;
	t_list_env	*debut;

	list1 = list_env;
	debut = list1;
	while (list_env != NULL)
	{
		list1 = debut;
		while (list1 != NULL)
		{
			if (ft_strcmpp(list1->variable, (list_env->variable)) > 0)
			{
				tmp = list1->variable;
				list1->variable = list_env->variable;
				list_env->variable = tmp;
				tmp = list1->valeur;
				list1->valeur = list_env->valeur;
				list_env->valeur = tmp;
				list1 = debut;
			}
			list1 = list1->next;
		}
		list_env = list_env->next;
	}
	return (debut);
}

void	ft_export(t_list_env *list_env, char **args, t_garbage **garb)
{
	int			c;
	t_export	index;

	c = ft_strlen_argc(args);
	index.i = 1;
	index.j = 1;
	index.c = 0;
	if (c == 1)
	{
		ft_print_env_ex(ex_sort(list_env, NULL));
	}
	else
	{
		check_args(&list_env, index, args, garb);
	}
}
