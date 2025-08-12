/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/12 20:37:30 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_dollar_dquote(char *value, int *i, int exit_code,
		t_expand_ctx *ctx)
{
	char	*result;
	int		start;
	char	raw[3];

	while (value[*i] == '$')
		(*i)++;
	if (value[*i] == '\0')
		return (NULL);
	if (value[*i] == '?')
	{
		result = ft_itoa(exit_code, ctx->garb);
		(*i)++;
		return (result);
	}
	if (ft_isalpha(value[*i]) || value[*i] == '_')
	{
		start = *i;
		while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
			(*i)++;
		result = get_env_value(ft_substr(value, start, *i - start, ctx->garb),
				ctx->env, ctx->garb);
		return (result);
	}
	1 && (raw[0] = '$', raw[1] = value[*i], raw[2] = '\0', i++);
	return (ft_strdup(raw, ctx->garb));
}


// static char	*expand_dollar_dquote(char *value, int *i, int exit_code,
// 		t_expand_ctx *ctx)
// {
// 	char	*result;
// 	int		start;
// 	char	raw[3];

// 	while (value[*i] == '$')
// 		(*i)++;
// 	if (value[*i] == '\0')
// 		return (NULL);
// 	if (value[*i] == '?')
// 	{
// 		result = ft_itoa(exit_code, ctx->garb);
// 		(*i)++;
// 		return (result);
// 	}
// 	if (ft_isalpha(value[*i]) || value[*i] == '_')
// 	{
// 		start = *i;
// 		while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
// 			(*i)++;
// 		result = get_env_value(ft_substr(value, start, *i - start, ctx->garb),
// 				ctx->env, ctx->garb);
// 		return (result);
// 	}
// 	raw[0] = '$';
// 	raw[1] = value[*i];
// 	raw[2] = '\0';
// 	(*i)++;
// 	return (ft_strdup(raw, ctx->garb));
// }

char	*expand_token_double_quotes(char *value,
		int exit_code, t_list_env *env, t_garbage **garb)
{
	t_expand_ctx	ctx;
	int				i;
	char			*res;
	char			*tmp;
	char			*exp;

	ctx.exit_code = exit_code;
	ctx.env = env;
	ctx.garb = garb;
	i = 0;
	res = ft_strdup("", garb);
	while (value[i])
	{
		if (value[i] == '$')
		{
			exp = expand_dollar_dquote(value, &i, exit_code, &ctx);
			if (!exp)
				return (value);
			tmp = ft_strjoin(res, exp, garb);
			res = tmp;
		}
		else
		{
			tmp = ft_strjoin(res, ft_substr(value, i, 1, garb), garb);
			i++;
			res = tmp;
		}
	}
	return (res);
}

// char	*expand_token_double_quotes(char *value,
// 		int exit_code, t_list_env *env, t_garbage **garb)
// {
// 	int			i = 0;
// 	char		*res = ft_strdup("", garb);
// 	char		*tmp;
// 	while (value[i])
// 	{
// 		if (value[i] == '$')
// 		{
// 			while (value[i] == '$')
// 				i++;
// 			if (value[i] == '\0')
// 				return (value);
// 			if (value[i] == '?')
// 			{
// 				char *exit_str = ft_itoa(exit_code, garb);
// 				char *new_res = ft_strjoin(res, exit_str, garb);
// 				res = new_res;
// 				i++;
// 			}
// 			else if (ft_isalpha(value[i]) || value[i] == '_')
// 			{
// 				int start = i;
// 				while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
// 					i++;
// 				char *var = ft_substr(value, start, i - start, garb);
// 				char *val = get_env_value(var, env, garb);
// 				tmp = ft_strjoin(res, val, garb);
// 				res = tmp;
// 			}
// 			else
// 			{
// 				char raw[3] = {'$', value[i], '\0'};
// 				tmp = ft_strjoin(res, raw, garb);
// 				res = tmp;
// 				i++;
// 			}
// 		}
// 		else
// 		{
// 			char c[2] = {value[i], '\0'};
// 			tmp = ft_strjoin(res, c, garb);
// 			res = tmp;
// 			i++;
// 		}
// 	}
// 	return (res);
// }



static int	should_expand(t_token *curr, t_parsing_context ctx)
{
	if (ctx.quoted_flag == 2) 
		return (0);
	if (ctx.quoted_flag == 1)
		return (1);
	if (curr->value[0] == '$' && curr->value[1] == '"')
		return (0);
	return (1);
}

static char	*expand_value(t_token *curr, t_expand_ctx *ctx1,
		t_parsing_context ctx)
{
	if (ctx.quoted_flag == 1)
	{
		return (expand_token_double_quotes(
			curr->value, ctx1->exit_code, ctx1->env, ctx1->garb));
	}
	return (expand_token(
		curr->value, ctx1->exit_code, ctx1->env, ctx1->garb));
}

// void	expand_all_tokens(t_token **tokens, int exit_code,
// 		t_list_env *env, t_parsing_context ctx)
// {
// 	t_token			*curr;
// 	t_expand_ctx	ctx1;
// 	t_token			*prev;
// 	t_token			*new_tokens;

// 	1 && (curr = *tokens , ctx1.env = env);
// 	ctx1.exit_code = exit_code;
// 	ctx1.garb = ctx.garb;
// 	while (curr)
// 	{
// 		if (!should_expand(curr, ctx))
// 		{
// 			curr = curr->next;
// 			continue ;
// 		}
// 		curr->value = expand_value(curr, &ctx1, ctx);
// 		if ( ctx.quoted_flag == 0)
// 		{
// 			new_tokens = split_tokens_by_space(curr->value, ctx1.garb);
// 			replace_token(tokens, curr, new_tokens);
// 			if (new_tokens)
// 			{
// 				prev = get_last_token(new_tokens);
// 				curr = prev->next;
// 				continue ;
// 			}
// 		}
// 		curr = curr->next;
// 	}
// }







static t_token	*handle_expanded_tokens(t_token **tokens, t_token *curr,
		t_expand_ctx *ctx1, t_parsing_context ctx)
{
	(void) ctx;
	t_token	*new_tokens;
	//t_token	*prev;

	new_tokens = split_tokens_by_space(curr->value, ctx1->garb, curr->type);
	replace_token(tokens, curr, new_tokens);
	// if (new_tokens)
	// {
	// 	prev = get_last_token(new_tokens);
	// 	return (curr->next);
	// }
	return (curr->next);
}


void	expand_all_tokens(t_token **tokens, int exit_code,
		t_list_env *env, t_parsing_context ctx)
{
	t_token		*curr;
	t_expand_ctx	ctx1;

	curr = *tokens;
	ctx1.env = env;
	ctx1.exit_code = exit_code;
	ctx1.garb = ctx.garb;
	while (curr)
	{
		if (!should_expand(curr, ctx))
		{
			curr = curr->next;
			continue ;
		}
		curr->value = expand_value(curr, &ctx1, ctx);
		if (ctx.quoted_flag == 0)
			curr = handle_expanded_tokens(tokens, curr, &ctx1, ctx);
		else
			curr = curr->next;
	}
}
