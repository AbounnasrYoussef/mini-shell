/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:49:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/26 15:09:33 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char *ft_pwd(t_list_env *env)
{
	char *buffer;
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
	{
		while (env != NULL)
		{
			if (ft_strcmpp(env->variable, "PWD") == 0)
			{
				buffer = env->valeur_vari;
			}
			env = env->next;
		}
	}
	return buffer;
}
