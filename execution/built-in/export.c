/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:10:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/30 17:22:44 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

#include <stdio.h>

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

void repmlacer_elem(t_list_env **list_env, char *var, char *arg, int d)
{
	t_list_env *l_env;
	
	l_env =  *list_env;
	while (l_env != NULL)
	{
		if (ft_strcmpp((l_env)->variable, var) == 0)
		{
			if (d == 1)
			{
				(l_env)->valeur_vari = ft_concat((l_env)->valeur_vari , arg);
			}
			else
				(l_env)->valeur_vari = arg;
		}	
		(l_env) = (l_env)->next;
	}
}

void ajout_exp_elem_help(t_list_env **list_env, char *args, int i, int c, int d, char **arg_varia)
{
	while (args[i] != '\0')
	{
		arg_varia[1][c] = args[i];
		c++;
		i++;
	}
	if (verif_exist(list_env, arg_varia[0]) == 0)
	{
		ft_lstadd_backk(list_env, ft_lstneww(arg_varia[0], arg_varia[1], args));
	}
	else
	{
		
		if (arg_varia[1] != NULL)
		{
			repmlacer_elem(list_env, arg_varia[0], arg_varia[1], d);
		}
			
	}
}

void ajout_exp_elem(t_list_env **list_env, char *args, int i, int j)
{
	int d;
	char **arg_varia;

	d = 0;
	arg_varia = malloc(2 * sizeof(char *));
	arg_varia[0] = malloc(200);
	while (args[i] != '\0' && args[i] != '=' && args[i] != '+')
	{	
		arg_varia[0][j] = args[i];
		i++;
		j++;
	}
	if (args[i] == '+' && args[i+1] == '=')
	{
		d = 1;
		i += 2;
	}
	else if (args[i] == '=')
		i++;
	if (args[i] == '\0')
		arg_varia[1] = NULL;
	else
		arg_varia[1] = malloc(200);
	ajout_exp_elem_help(list_env,  args, i, 0, d, arg_varia);
}
void error_export(char **args, int i)
{
	write(2, "export: `", 9);
	write(2, args[i], ft_strlenn(args[i]));
	write(2, "' not a valid identifier\n", 25);
}

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
