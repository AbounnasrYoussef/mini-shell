/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:10:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/06/22 17:00:36 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

#include <stdio.h>

t_list *sort(t_list *list_env)
{
	char *s1;
	t_list *list1;
	t_list *list2;
	t_list *tmp;
	t_list *debut;
	list1 = list_env;
	debut = list_env;
	while(list1 != NULL)
	{
		list_env = debut;
		
		while(list_env != NULL)
		{
			//printf("%s", list1->ligne);
			if (ft_strcmp(list1->ligne, (list_env->ligne)) < 0)
			{
				list2 = list_env->ligne;
				
			}
			printf("%s", list2->ligne);
			list_env = list_env->next;
		}
		//printf("%s", list2->ligne);
		//tmp = list1;
		//list1->ligne = list2->ligne;
		//list2->ligne = tmp->ligne;
		
		list1 = list1->next;
	}
	return list1;

}
//void ft_export(char **str)
//{

//}

int main(int argc, char **argv, char **env)
{
	//ft_export(env);
	//printf("%s", env[0]);
	sort(ft_env(env));
	
}