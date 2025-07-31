/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:23:13 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 14:21:49 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char	*get_env_value(char *name, t_list_env *env, t_garbage **garb)
{
	while (env)
	{
		if (env->variable && ft_strcmp(env->variable, name) == 0)
			return (ft_strdup(env->valeur_vari, garb));
		env = env->next;
	}
	return (ft_strdup("", garb));
}

// Expansion du $ : gère $$, $?, $VAR, $ seul, $ suivi de char invali
char	*expand_dollar(char *value, int *i, int exit_code, t_list_env *env, t_garbage **garb)
{
	char	*var_name;
	char	*res;

	(void)exit_code;

	if (!value[*i + 1])
	{
		(*i)++;
		return (ft_strdup("$", garb)); // $ en fin de chaîne => $
	}
	if (value[*i + 1] == '$')
	{
		(*i) += 2;
		return (ft_strdup("$$", garb)); // $$ reste $$
	}
	if (value[*i + 1] == '?')
	{
		(*i) += 2;
		return (ft_itoa(ft_exit_status(0 , 0), garb)); // $? remplacé par exit_code
	}
	(*i)++;
	if (!is_valid_var_char(value[*i]))
	{
		// $ suivi d'un char non valide, on ne consomme pas ce char
		return (ft_strdup("$", garb));
	}
	int start = *i;
	while (value[*i] && is_valid_var_char(value[*i]))
		(*i)++;
	var_name = ft_substr(value, start, *i - start, garb);
	res = get_env_value(var_name, env, garb);
	return (res);
}
