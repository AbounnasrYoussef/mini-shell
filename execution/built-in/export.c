/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:10:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/14 21:17:33 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

#include <stdio.h>

int verif_exist(t_list **list_env, char *arg)
{
	t_list *l_env;

	l_env = *list_env;
	while (l_env != NULL)
	{
		if (ft_strcmp((l_env)->variable, arg) == 0)
			return 1;
		(l_env) = (l_env)->next;
	}
	return 0;
}

void repmlacer_elem(t_list **list_env, char *var, char *arg)
{
	t_list *l_env;
	
	l_env =  *list_env;
	while (l_env != NULL)
	{
		if (ft_strcmp((l_env)->variable, var) == 0)
		{
			(l_env)->valeur_vari = arg;
		}
			
		(l_env) = (l_env)->next;
	}
}

void ajout_exp_elem(t_list **list_env, char **args)
{
	int i;
	int j;
	int c;
	char **arg_varia;

	i = 1;
	j = 0;
	arg_varia = malloc(2 * sizeof(char *));
	
	while (args[i] != NULL)
	{
		arg_varia[0] = malloc(200);
		while(args[i][j] != '\0')
		{
			while (args[i][j] != '\0' && args[i][j] != '=')
			{	
				arg_varia[0][j] = args[i][j];
				j++;
			}
			c = 0;
			j++;

			arg_varia[1] = NULL;
			if (args[i][j] == '\0')
				arg_varia[1] = NULL;
			else
				arg_varia[1] = malloc(200);
			while (args[i][j] != '\0')
			{
				arg_varia[1][c] = args[i][j];
				c++;
				j++;
			}
			if (verif_exist(list_env, arg_varia[0]) == 0)
			{
				ft_lstadd_back(list_env, ft_lstnew(arg_varia[0], arg_varia[1], args[i]));
			}
			else
			{
				repmlacer_elem(list_env, arg_varia[0], arg_varia[1]);
			}
		}
		i++;
	}
}

int check_args(t_list **list_env, char **args)
{
	int i;
	int j;

	i = 1;
	j = 0;
	
	while (args[i] != NULL)
	{
		if (!(args[i][0] == '_' ||
			(args[i][0] >= 'a' && args[i][0] <= 'z')
			|| (args[i][0] >= 'A' && args[i][0] <= 'Z')))
		{
			return -1;
		}	
		while(args[i][j] != '\0')
		{
			if (!(args[i][j] == '_' || args[i][j] == '=' 
				|| (args[i][j] >= 'a' && args[i][j] <= 'z') 
				|| (args[i][j] >= 'A' && args[i][j] <= 'Z') 
				|| (args[i][j] >= '0' && args[i][j] <= '9')))
				return (-1);
			j++;
		}
		j = 0;
		i++;
	}
	ajout_exp_elem(list_env, args);
	return (0);
}



t_list *ex_sort(t_list *list_env)
{
	t_list	*list1;
	char	*tmp;;
	t_list	*debut;
	
	list1 = list_env;
	debut = list1;
	while (list_env != NULL)
	{
		list1 = debut;
		while(list1 != NULL)
		{
			if (ft_strcmp(list1->variable, (list_env->variable)) > 0)
			{
				tmp = list1->variable;
				list1->variable = list_env->variable;
				list_env->variable = tmp;
				
				tmp = list1->valeur_vari;
				list1->valeur_vari = list_env->valeur_vari;
				list_env->valeur_vari = tmp;
				
				tmp = list1->ligne;
				list1->ligne = list_env->ligne;
				list_env->ligne = tmp;
				
				list1 = debut;
			}
			list1 = list1->next;	
		}
		list_env = list_env->next;
	}
	return debut;
}



void ft_export(t_list *list_env, char **args, int argc)
{
	t_list *new_list;
	if (argc == 1)
	{
		ft_print_env(ex_sort(list_env));
	}
	else
	{
		if (check_args(&list_env, args) == -1)
		{
			printf("not a valid identifier");
			exit(-1);
		}
	}
}

