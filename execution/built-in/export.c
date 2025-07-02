/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:10:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/02 09:13:41 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

#include <stdio.h>

t_list *sort(t_list *list_env)
{
	t_list	*list1;
	char	*tmp;;
	t_list	*debut;
	int i;
	
	list1 = list_env;
	debut = list1;
	i = 0;
	while (list_env != NULL)
	{
		list1 = debut;
		while(list1 != NULL)
		{
			//printf("aaaaaaaa %s \n\n", list1->ligne);
			//printf("pppppppp %s \n\n", list_env->ligne);
			//printf("cmp : %d\n\n", ft_strcmp(list1->ligne, (list_env->ligne)));
			if (ft_strcmp(list1->ligne, (list_env->ligne)) > 0)
			{
				tmp = list1->ligne;
				list1->ligne = list_env->ligne;
				list_env->ligne = tmp;
				list1 = debut;
			}
			list1 = list1->next;	
			i++;
		}
		list_env = list_env->next; 
	}
	return debut;
}

int main(int argc, char **argv, char **env)
{
	t_list *at;
	t_list *srt;
	at = ft_env(env);
	//printf("%s\n", at->ligne);
	srt = sort(ft_env(env));
	while (srt != NULL)
	{
		printf("%s\n", srt->ligne);
		srt = srt->next;
	}
}