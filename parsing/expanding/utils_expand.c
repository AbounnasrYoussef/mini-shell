/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:36:56 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/20 14:54:06 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_red(char *value, t_expand_ctx *ctx, t_garbage **garb)
{
	t_inf_expand_red	inf_red;

	inf_red.content = expand_dollar(value, &inf_red.i, ctx);
	if (check_name(inf_red.content, garb))
		return (NULL);
	inf_red.res = ft_strdup("", garb);
	while (value[inf_red.i])
	{
		if (value[inf_red.i] == '\'')
			append_single_quote(value, &inf_red.i, &inf_red.res, garb);
		else if (value[inf_red.i] == '"')
			append_double_quote(value, &inf_red.i, &inf_red.res, *ctx);
		else if (value[inf_red.i] == '$')
			inf_red.res = ft_strjoin(inf_red.res, inf_red.content, garb);
		else
		{
			inf_red.tmp = ft_substr(value, inf_red.i, 1, garb);
			inf_red.res = ft_strjoin(inf_red.res, inf_red.tmp, garb);
			inf_red.i++;
		}
	}
	if (ft_strcmpp(inf_red.res, "") == 0 && value[0] == '$'
		&& get_env_value(&value[1], ctx->env, garb) == NULL)
		return (NULL);
	return (inf_red.res);
}

t_token	*check_if_red(t_token *curr, t_garbage **garb,
		t_expand_ctx ctx1)
{
	curr = curr->next;
	if (curr)
	{
		curr->value = expand_red(curr->value, &ctx1, garb);
		return (curr->next);
	}
	return (curr);
}
