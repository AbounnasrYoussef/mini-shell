/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 18:11:44 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*process_token(t_token *curr, t_token **tokens,
						t_token **prev, t_expand_ctx *ctx)
{
	char		*expanded;
	char		*cleaned;
	t_token		*to_delete;

	if (curr->quoted == 1)
		expanded = ft_strdup(curr->value, ctx->garb);
	else
		expanded = expand_token(curr->value,
				ctx->exit_code, ctx->env, ctx->garb);
	cleaned = ft_strtrim_custom(expanded, ctx->garb, curr->quoted);
	if (!cleaned || cleaned[0] == '\0')
	{
		to_delete = curr;
		curr = curr->next;
		if (!*prev)
			*tokens = to_delete->next;
		else
			(*prev)->next = to_delete->next;
		return (curr);
	}
	curr->value = cleaned;
	*prev = curr;
	return (curr->next);
}

void	expand_all_tokens(t_token **tokens, int exit_code
		, t_list_env *env, t_garbage **garb)
{
	t_token			*curr;
	t_token			*prev;
	t_expand_ctx	ctx;

	curr = *tokens;
	prev = NULL;
	ctx.exit_code = exit_code;
	ctx.env = env;
	ctx.garb = garb;
	while (curr)
		curr = process_token(curr, tokens, &prev, &ctx);
}
