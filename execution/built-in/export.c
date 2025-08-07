/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:10:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/07 11:14:11 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	verif_exist(t_list_env **list_env, char *arg)
{
	t_list_env	*l_env;

	l_env = *list_env;
	while (l_env != NULL)
	{
		if (ft_strcmpp((l_env)->variable, arg) == 0)
		{
			return (1);
			break ;
		}
		(l_env) = (l_env)->next;
	}
	return (0);
}

void	chng_el(t_list_env **env, char *var, char *arg, int d, t_garbage **garb)
{
	t_list_env	*l_env;

	l_env = *env;
	while (l_env != NULL)
	{
		if (ft_strcmpp((l_env)->variable, var) == 0)
		{
			if (d == 1)
			{
				(l_env)->valeur = ft_concat((l_env)->valeur, arg, garb);
			}
			else
				(l_env)->valeur = arg;
		}
		(l_env) = (l_env)->next;
	}
}

void	exp_el_help(t_list_env **list_env, char *args, t_export indx, char **arg_varia, t_garbage **garb)
{
	int	k;

	k = 0;
	while (args[indx.i] != '\0')
	{
		indx.i++;
		indx.j++;
	}
	indx.i = indx.i - indx.j;
	arg_varia[1] = ft_malloc(garb, (indx.j + 1));
	while (args[indx.i] != '\0')
	{
		arg_varia[1][k] = args[indx.i];
		k++;
		indx.i++;
	}
	arg_varia[1][k] = '\0';
	if (verif_exist(list_env, arg_varia[0]) == 0)
		ft_lstadd_backk(list_env, ft_lstneww(arg_varia[0], arg_varia[1], garb));
	else
	{
		if (arg_varia[1] != NULL && arg_varia[1][0] != '\0')
			chng_el(list_env, arg_varia[0], arg_varia[1], indx.c, garb);
	}
}

void	export_el(t_list_env **env, char *args, t_export indx, t_garbage **garb)
{
	char	**arg_varia;

	indx.i = 0;
	indx.j = 0;
	indx.c = 0;
	arg_varia = ft_malloc(garb, 2 * sizeof(char *));
	while (args[indx.j] != '\0' && args[indx.j] != '=' && args[indx.j] != '+')
		indx.j++;
	arg_varia[0] = ft_malloc(garb, indx.j + 1);
	while (indx.i < indx.j)
	{
		arg_varia[0][indx.i] = args[indx.i];
		indx.i++;
	}
	arg_varia[0][indx.i] = '\0';
	if (args[indx.i] == '+' && args[indx.i + 1] == '=')
	{
		indx.c = 1;
		indx.i += 2;
	}
	else if (args[indx.i] == '=')
		indx.i++;
	if (args[indx.i] == '\0')
		arg_varia[1] = NULL;
	indx.j = 0;
	exp_el_help(env, args, indx, arg_varia, garb);
}

void	error_export(char **args, int i)
{
	write(2, "export: `", 9);
	write(2, args[i], ft_strlenn(args[i]));
	write(2, "' not a valid identifier\n", 25);
	ft_exit_status(1, 1);
}
