/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:54:21 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/03 17:45:30 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list_env	*ft_lstnew(void *variable, void *valeur_vari)
{
	t_list_env	*list1;

	list1 = malloc(sizeof(t_list_env));
	if (list1 == NULL)
	{
		return (NULL);
	}
	list1->variable = variable;
	list1->valeur_vari = valeur_vari;
	list1->next = NULL;
	return (list1);
}

void	ft_lstadd_back(t_list_env **lst, t_list_env *new)
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

t_list_env	*ft_env(char **str)
{
	t_list_env	*copy_env;
	t_list_env	*debut_env;
	char		**splitt;
	int			i;
	int			j;

	copy_env = NULL;
	i = 0;
	j = 0;
	while (str[i] != NULL )
	{
		splitt = i_split(str[i], '=');
		ft_lstadd_back(&copy_env, ft_lstnew(splitt[0], splitt[1]));
		if (i == 0)
			debut_env = copy_env;
		i++;
	}
	return (debut_env);
}
