/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:13:22 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/11 00:43:22 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_print_env_ex(t_list_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "_") != 0)
		{
			if (env->val != NULL)
				printf("declare -x %s=\"%s\"\n", env->variable, env->val);
			else
				printf("declare -x %s\n", env->variable);
		}
		env = env->next;
	}
}

void	ft_print_env(t_list_env *env)
{
	while (env != NULL)
	{
		if (env->val != NULL && ft_strcmpp(env->val, "") != 0)
		{
			printf("%s=\"%s\"\n", env->variable, env->val);
		}
		env = env->next;
	}
}

int	norm_help_built(t_list_env **env, char **cmd)
{
	ft_unset(env, cmd);
	if (check_exist_pwd(*env) == 1)
		ft_change_oldpwd(env);
	return (0);
}
