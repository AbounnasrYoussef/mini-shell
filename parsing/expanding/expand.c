/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/26 15:19:08 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_token(char *value, int exit_code,
				t_list_env *env, garbage **garb)
{
	int		i = 0;
	char	*res = ft_strdup("", garb);
	char	*tmp;

	while (value[i])
	{
		if (value[i] == '\'')
		{
			int start = ++i;
			while (value[i] && value[i] != '\'')
				i++;
			tmp = ft_substr(value, start - 1, i - start + 2, garb);
			res = ft_strjoin(res, tmp, garb);
			i++;
		}
		else if (value[i] == '"')
		{
			int start = ++i;
			char *part = ft_strdup("", garb);
			while (value[i] && value[i] != '"')
			{
				if (value[i] == '$')
					part = ft_strjoin(part, expand_dollar(value, &i, exit_code, env, garb), garb);
				else
				{
					tmp = ft_substr(value, i, 1, garb);
					part = ft_strjoin(part, tmp, garb);
					i++;
				}
			}
			res = ft_strjoin(res, part, garb);
			i++;
		}
		else if (value[i] == '$')
			res = ft_strjoin(res, expand_dollar(value, &i, exit_code, env, garb), garb);
		else
		{
			tmp = ft_substr(value, i, 1, garb);
			res = ft_strjoin(res, tmp, garb);
			i++;
		}
	}
	return (res);
}


void	expand_all_tokens(t_token *tokens, int exit_code,
				t_list_env *env, garbage **garb)
                // code de retour du dernier commande executer
{
	char	*expanded;

	while (tokens) //tous les tokens
	{
		if (tokens->type == WORD && ft_strchr(tokens->value, '$')) // if ila kane token word o kayn fih dollar
		{
			expanded = expand_token(tokens->value, exit_code, env, garb);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}

