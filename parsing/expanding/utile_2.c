/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:27:14 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/26 15:17:22 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


#include "minishell.h"

static void	append_single_quote(const char *val, int *i, char **res,
		garbage **garb)
{
	int		start;
	char	*tmp;

	start = ++(*i);
	while (val[*i] && val[*i] != '\'')
		(*i)++;
	tmp = ft_substr_gc(val, start - 1, *i - start + 2, garb);
	*res = ft_strjoin_gc(*res, tmp, garb);
	(*i)++;
}

static void	append_double_quote(const char *val, int *i, char **res,
		t_expand_ctx ctx)
{
	int		start;
	char	*tmp;
	char	*part;

	start = ++(*i);
	part = ft_strdup_gc("", ctx.garb);
	while (val[*i] && val[*i] != '"')
	{
		if (val[*i] == '$')
			part = ft_strjoin_gc(part,
					expand_dollar(val, i, ctx.exit_code,
						ctx.env, ctx.garb), ctx.garb);
		else
		{
			tmp = ft_substr_gc(val, *i, 1, ctx.garb);
			part = ft_strjoin_gc(part, tmp, ctx.garb);
			(*i)++;
		}
	}
	*res = ft_strjoin_gc(*res, part, ctx.garb);
	(*i)++;
}

char	*expand_token(char *value, int exit_code,
			t_list_env *env, garbage **garb)
{
	int			i;
	char		*res;
	char		*tmp;
	t_expand_ctx	ctx;

	i = 0;
	res = ft_strdup_gc("", garb);
	ctx.env = env;
	ctx.exit_code = exit_code;
	ctx.garb = garb;
	while (value[i])
	{
		if (value[i] == '\'')
			append_single_quote(value, &i, &res, garb);
		else if (value[i] == '"')
			append_double_quote(value, &i, &res, ctx);
		else if (value[i] == '$')
			res = ft_strjoin_gc(res,
					expand_dollar(value, &i, exit_code, env, garb),
					garb);
		else
		{
			tmp = ft_substr_gc(value, i, 1, garb);
			res = ft_strjoin_gc(res, tmp, garb);
			i++;
		}
	}
	return (res);
}
