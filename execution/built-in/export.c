/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:10:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/06/20 00:56:24 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

typedef struct s_list
{
	void	*variable;
	void 	*valeur_vari;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *variable, void *valeur_vari)
{
	t_list	*list1;

	list1 = malloc(sizeof(t_list));
	if (list1 == NULL)
	{
		return (NULL);
	}
	list1->variable = variable;
	list1->valeur_vari = valeur_vari;
	list1->next = NULL;
	return (list1);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

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

#include <stdio.h>
void ft_export(char **str)
{
	t_list *copy_env;
	t_list *debut_env;
	char **splitt;
	int i;
	int j;
	
	i = 0;
	j = 0;
	debut_env = copy_env;
	while (str[i] != NULL )
	{
		splitt = ft_split(str[i], '=');
		ft_lstadd_back(&copy_env, ft_lstnew(splitt[0], splitt[1]));
		i++;
	}

	//while(debut_env != NULL)
	//{
	//	printf("%s", debut_env->variable);
	//	debut_env = debut_env->next;
	//}
}

int main(int argc, char **argv, char **env)
{
	ft_export(env);
	//printf("%s", env[0]);
}