/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:33:27 by arahhab           #+#    #+#             */
/*   Updated: 2025/06/22 16:42:02 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_list	*ft_lstnew(void *variable, void *valeur_vari, void *ligne)
{
	t_list	*list1;

	list1 = malloc(sizeof(t_list));
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

t_list *ft_env(char **str)
{
	t_list *copy_env = NULL;
	t_list *debut_env;
	t_list *new;
	char **splitt;
	int i;
	int j;
	
	i = 0;
	j = 0;
	
	
	while (str[i] != NULL )
	{
		splitt = ft_split(str[i], '=');
		ft_lstadd_back(&copy_env, ft_lstnew(splitt[0], splitt[1], str[i]));
		if(i == 0)
			debut_env = copy_env;
		//ft_put_string(str[i]);
		//ft_put_string(copy_env->variable);
		//ft_put_string("=");
		//ft_put_string(copy_env->valeur_vari);
		
		//ft_put_string("\n");
		copy_env = copy_env->next;
		i++;
	}
	return (debut_env);
}

//int main(int argc, char **argv, char **env)
//{
//	t_list *ls1 ;
//	ls1 = ft_env(env);
//	printf("%s", ls1->ligne);
//}