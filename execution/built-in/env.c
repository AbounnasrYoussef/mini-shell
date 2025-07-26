/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:33:27 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/26 13:42:22 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_list_env	*ft_lstneww(void *variable, void *valeur_vari, void *ligne)
{
	t_list_env	*list1;

	list1 = malloc(sizeof(t_list_env));
	if (list1 == NULL)
	{
		return (NULL);
	}
	list1->variable = variable;
	list1->valeur_vari = valeur_vari;
	list1->ligne = ligne;
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

t_list_env *ft_envvv(char **str)
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
		splitt = ft_splitt(str[i], '=');
		ft_lstadd_backk(&copy_env, ft_lstneww(splitt[0], splitt[1], str[i]));
		if(i == 0)
		{
			debut_env = copy_env;
		}
		i++;
	}
	return (debut_env);
}


