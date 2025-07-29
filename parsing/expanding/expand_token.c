/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:38:12 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 17:56:12 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char	*expand_token(char *value, int exit_code, t_list_env *env, garbage **garb)
{
	int			i;
	char		*res;
	char		*tmp;
	t_expand_ctx	ctx;

	i = 0;
	ctx.env = env;
	ctx.exit_code = exit_code;
	ctx.garb = garb;
	res = ft_strdup("", garb);
	while (value[i])
	{
		if (value[i] == '\'')
			append_single_quote(value, &i, &res, garb);
		else if (value[i] == '"')
			append_double_quote(value, &i, &res, ctx);
		else if (value[i] == '$')
			res = ft_strjoin(res,
					expand_dollar(value, &i, exit_code, env, garb),
					garb);
		else
		{
			tmp = ft_substr(value, i, 1, garb);
			res = ft_strjoin(res, tmp, garb);
			i++;
		}
	}
	return (res);
}