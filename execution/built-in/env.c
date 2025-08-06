/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:33:27 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/06 16:07:43 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_list_env	*ft_lstneww(void *variable, void *valeur_vari, t_garbage **garb)
{
	t_list_env	*list1;

	(void)garb;
	list1 = ft_malloc(garb, sizeof(t_list_env));
	if (list1 == NULL)
	{
		return (NULL);
	}
	list1->variable = variable;
	list1->valeur_vari = valeur_vari;
	list1->next = NULL;
	return (list1);
}

void	ft_lstadd_backk(t_list_env **lst, t_list_env *new)
{
	t_list_env	*temp;

	if (new == NULL || lst == NULL)
	{
		return ;
	}
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
}

t_list_env *ft_envvv(char **str, t_garbage **garb)
{
	t_list_env *copy_env = NULL;
	t_list_env *debut_env;
	char **splitt;
	int i;
	int j;
	
	i = 0;
	j = 0;
	
	while (str[i] != NULL )
	{
		splitt = ft_splitt(str[i], '=', garb);
		if (splitt[1] != NULL)
		{
			ft_lstadd_backk(&copy_env, ft_lstneww(splitt[0], splitt[1], garb));
			if(ft_strcmpp(splitt[0], "PWD") == 0)
			{
				ft_lstadd_backk(&copy_env, ft_lstneww("PO", splitt[1], garb));
			}
		}
		else
		{
			ft_lstadd_backk(&copy_env, ft_lstneww(splitt[0], NULL, garb));
		}
		if(i == 0)
		{
			debut_env = copy_env;
		}
		i++;
	}
	return (debut_env);
}


