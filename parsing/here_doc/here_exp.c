/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:26:51 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/11 14:50:54 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_dollar(char *line, int *i, char **tmp, t_expand_ctx *ctx)
{
	if (line[*i] == '?')
	{
		char *exit_str = ft_itoa(ft_exit_status(0 , 0), ctx->garb);
		*tmp = ft_strjoin(*tmp, exit_str, ctx->garb);
		(*i)++;
		return (0);
	}
	else if (is_valid_var_char(line[*i]))
	{
		int start = *i;
		while (is_valid_var_char(line[*i]))
			(*i)++;
		char *varname = ft_substr(line, start, *i - start, ctx->garb);
		char *val = get_env_value(varname, ctx->env, ctx->garb);
		if (!val)
			val = ft_strdup("", ctx->garb);
		*tmp = ft_strjoin(*tmp, val, ctx->garb);
		return (0);
	}
	else
	{
		*tmp = ft_strjoin(*tmp, "$", ctx->garb);
		return (1);
	}
}

int heredoc_expansion(char *line, t_list_env *env, t_garbage **garb, char **res)
{
	int			i;
	int			in_sq;
	int			in_dq;
	char		*tmp;
	t_expand_ctx ctx = { env, garb };

	i = 0;
	in_sq = 0;
	in_dq = 0;
	tmp = ft_strdup("", garb);
	if (!tmp)
		return (-1);
	while (line[i])
	{
		if (line[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (line[i] == '\"' && !in_sq)
			in_dq = !in_dq;
		else if (line[i] == '$' && !in_sq)
		{
			i++;
			if (handle_dollar(line, &i, &tmp, &ctx))
				continue ;
			continue ;
		}
		else
		{
			char str[2] = { line[i], '\0' };
			tmp = ft_strjoin(tmp, str, garb);
			i++;
		}
	}
	*res = tmp;
	return (0);
}
