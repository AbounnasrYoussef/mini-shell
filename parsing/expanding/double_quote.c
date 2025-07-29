/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:22:31 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 17:42:47 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	append_double_quote(const char *val, int *i, char **res, t_expand_ctx ctx)
{
	char	*part;
	char	*tmp;

	(*i)++;
	part = ft_strdup("", ctx.garb);
	while (val[*i] && val[*i] != '"')
	{
		if (val[*i] == '$')
			part = ft_strjoin(part,
					expand_dollar((char *)val, i, ctx.exit_code, ctx.env, ctx.garb),
					ctx.garb);
		else
		{
			tmp = ft_substr(val, *i, 1, ctx.garb);
			part = ft_strjoin(part, tmp, ctx.garb);
			(*i)++;
		}
	}
	*res = ft_strjoin(*res, part, ctx.garb);
	if (val[*i] == '"')
		(*i)++;
}
