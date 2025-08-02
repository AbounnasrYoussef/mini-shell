/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:49:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/02 15:06:31 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char *ft_pwd(t_list_env *env)
{
	char *buffer;
	t_list_env *copy_env;

	copy_env = env;
	buffer = NULL;
	
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "PWD") == 0 
			|| ft_strcmpp(env->variable, "PO") == 0)
		{
			buffer = env->valeur_vari;
		}
		env = env->next;
	}
	if (getcwd(NULL, 0) != NULL)
		buffer = getcwd(NULL, 0);
	return buffer;
}
