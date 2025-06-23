/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:10:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/06/23 23:33:38 by arahhab          ###   ########.fr       */
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
	//printf("%s\n", list1->next->ligne);
	//while(list1 != NULL)
	//{
	//	list_env = debut;
	//	printf("%s\n", list1->ligne);
	//	while(list_env != NULL)
	//	{
			
	//		if (ft_strcmp(list1->ligne, (list_env->ligne)) < 0)
	//		{
	//			list2 = list_env->ligne;
				
	//		}
	//		printf("%s", list2->ligne);
	//		list_env = list_env->next;
	//	}
	//	//printf("%s", list2->ligne);
	//	//tmp = list1;
	//	//list1->ligne = list2->ligne;
	//	//list2->ligne = tmp->ligne;
		
	//	list1 = list1->next;
	//}
	return list1;

}
//void ft_export(char **str)
//{

//}

int main(int argc, char **argv, char **env)
{
	//ft_export(env);
	//printf("%s", env[0]);
	
	//sort(ft_env(env));
	//t_list *at;
	//at = ft_env(env);
	//printf("%s", at->next->ligne);
	
}