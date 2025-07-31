/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:38:19 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 15:20:44 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*new_token(char *value, type_token type, int i, t_garbage **garb)
{
	t_token	*tok;

	tok = ft_malloc(garb, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = ft_strdup(value, garb);
	tok->type = type;
	tok->join = 1;
	tok->quoted = i;
	tok->double_quote = 0;
	tok->next = NULL;
	return (tok);
}

static void	handle_quoted_part(const char *line, int *i, t_quote_ctx *ctx)
{
	char	quote;
	int		start;
	char	*substr;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
	{
		substr = ft_substr(line, start, *i - start, ctx->garb);
		*(ctx->res) = ft_strjoin(*(ctx->res), substr, ctx->garb);
		if (quote == '\'')
			*(ctx->quoted_flag) = 1;
		else if (quote == '"')
			*(ctx->quoted_flag) = 2;
		(*i)++;
	}
}

static char	*read_word_loop(const char *line, int *i, t_quote_ctx *ctx)
{
	char	*res;
	char	*word;
	int		start;

	res = ft_strdup("", ctx->garb);
	while (line[*i] && !skip_space(line[*i]) && !is_operator(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
			handle_quoted_part(line, i, ctx);
		else
		{
			start = *i;
			while (line[*i] && !skip_space(line[*i]) && !is_operator(line[*i])
				&& line[*i] != '\'' && line[*i] != '"')
				(*i)++;
			word = ft_substr(line, start, *i - start, ctx->garb);
			res = ft_strjoin(res, word, ctx->garb);
		}
	}
	return (res);
}

void	handle_word(const char *line, int *i
		, t_token **tokens, t_garbage **garb)
{
	char		*res;
	int			quoted_flag;
	t_quote_ctx	ctx;

	quoted_flag = 0;
	ctx.res = &res;
	ctx.quoted_flag = &quoted_flag;
	ctx.garb = garb;
	res = read_word_loop(line, i, &ctx);
	if (res && res[0] != '\0')
		add_token(tokens, new_token(res, WORD, quoted_flag, garb));
}
