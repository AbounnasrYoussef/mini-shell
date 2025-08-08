/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:49:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/08 16:42:19 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_pwd(t_list_env *env)
{
	char		*buffer;
	t_list_env	*copy_env;

	copy_env = env;
	buffer = NULL;
	if (getcwd(NULL, 0) != NULL)
		buffer = getcwd(NULL, 0);
	else
	{
		while (env != NULL)
		{
			if (ft_strcmpp(env->variable, "PWD") == 0
				|| ft_strcmpp(env->variable, "PO") == 0
				|| ft_strcmpp(env->variable, "OLD_PWD") == 0)
			{
				buffer = env->val;
				break;
			}
			env = env->next;
		}
	}
	if (buffer == NULL)
		buffer = "ahaha";
	return (buffer);
}
