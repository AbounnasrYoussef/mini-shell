/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:10:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/03 22:03:55 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int verif_exist(t_list_env **list_env, char *arg)
{
	t_list_env *l_env;

	l_env = *list_env;
	while (l_env != NULL)
	{
		if (ft_strcmpp((l_env)->variable, arg) == 0)
		{
			return 1;
			break;
		}	
		(l_env) = (l_env)->next;
	}
	return 0;
}

void repmlacer_elem(t_list_env **list_env, char *var, char *arg, int d, t_garbage **garb)
{
	t_list_env *l_env;
	
	l_env =  *list_env;
	while (l_env != NULL)
	{
		if (ft_strcmpp((l_env)->variable, var) == 0)
		{
			if (d == 1)
			{
				(l_env)->valeur_vari = ft_concat((l_env)->valeur_vari , arg, garb);
			}
			else
				(l_env)->valeur_vari = arg;
		}	
		(l_env) = (l_env)->next;
	}
}

void ajout_exp_elem_help(t_list_env **list_env, char *args, int i, int c, int d, char **arg_varia, t_garbage **garb)
{
	int k;

	k = 0;
	while (args[i] != '\0')
	{
		i++;
		c++;
	}
	i = i - c;
	arg_varia[1] = ft_malloc(garb, (c + 1));
	while (args[i] != '\0')
	{
		arg_varia[1][k] = args[i];
		k++;
		i++;
	}
	arg_varia[1][k] = '\0';
	if (verif_exist(list_env, arg_varia[0]) == 0)
	{
		ft_lstadd_backk(list_env, ft_lstneww(arg_varia[0], arg_varia[1], garb));
	}
	else
	{
		
		if (arg_varia[1] != NULL)
		{
			repmlacer_elem(list_env, arg_varia[0], arg_varia[1], d, garb);
		}
	}
}

void ajout_exp_elem(t_list_env **list_env, char *args, int i, int j, t_garbage **garb)
{
	int d;
	char **arg_varia;

	d = 0;
	arg_varia = ft_malloc(garb, 2 * sizeof(char *));
	
	while (args[j] != '\0' && args[j] != '=' && args[j] != '+')	
		j++;
	arg_varia[0] = ft_malloc(garb, j + 1);
	while (i < j)
	{	
		arg_varia[0][i] = args[i];
		i++;
	}
	arg_varia[0][i] = '\0';
	if (args[i] == '+' && args[i+1] == '=')
	{
		d = 1;
		i += 2;
	}
	else if (args[i] == '=')
		i++;
	if (args[i] == '\0')
		arg_varia[1] = NULL;
	ajout_exp_elem_help(list_env,  args, i, 0, d, arg_varia, garb);
}

void error_export(char **args, int i)
{
	write(2, "export: `", 9);
	write(2, args[i], ft_strlenn(args[i]));
	write(2, "' not a valid identifier\n", 25);
}
