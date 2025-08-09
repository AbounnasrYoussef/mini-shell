/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/09 12:28:28 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char	*expand_token_double_quotes(char *value,
		int exit_code, t_list_env *env, t_garbage **garb)
{
	int			i = 0;
	char		*res = ft_strdup("", garb);
	char		*tmp;

	while (value[i])
	{
		if (value[i] == '$')
		{
			i++;
			if (value[i] == '?')
			{
				char *exit_str = ft_itoa(exit_code, garb);
				char *new_res = ft_strjoin(res, exit_str, garb);
				res = new_res;
				i++;
			}
			else if (ft_isalpha(value[i]) || value[i] == '_')
			{
				int start = i;
				while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
					i++;
				char *var = ft_substr(value, start, i - start, garb);
				char *val = get_env_value(var, env, garb);
				tmp = ft_strjoin(res, val, garb);
				res = tmp;
			}
			else
			{
				char raw[3] = {'$', value[i], '\0'};
				tmp = ft_strjoin(res, raw, garb);
				res = tmp;
				i++;
			}
		}
		else
		{
			char c[2] = {value[i], '\0'};
			tmp = ft_strjoin(res, c, garb);
			res = tmp;
			i++;
		}
	}
	return (res);
}


static t_token	*process_token(t_token *curr, t_token **tokens,
						t_token **prev, t_expand_ctx *ctx)
{
	char		*expanded;
	t_token		*new_tokens;

	// On ne fait pas d'expansion pour les tokens après redirections
	if (*prev && ((*prev)->type == RDR_IN || (*prev)->type == RDR_OUT
		|| (*prev)->type == APPEND || (*prev)->type == HERE_DOC))
	{
		*prev = curr;
		return (curr->next);
	}

	// Si simple quotes (quoted_flag == 2), on ne fait aucune expansion, juste dupliquer
	if (curr->quoted == 2)
	{
		*prev = curr;
		return (curr->next);
	}

	// Si double quotes (quoted_flag == 1), expansion spécifique (respect des règles dans "")
	if (curr->quoted == 1)
		expanded = expand_token_double_quotes(curr->value, ctx->exit_code, ctx->env, ctx->garb);
	else
		// Sinon expansion normale (pas de quotes)
		expanded = expand_token(curr->value, ctx->exit_code, ctx->env, ctx->garb);

	if (!expanded)
		expanded = ft_strdup("", ctx->garb);

	// Suppression optionnelle des quotes (selon comportement voulu)
	char *cleaned = ft_strtrim_custom(expanded, ctx->garb, curr->quoted);

	// Si résultat vide et pas de quotes, on supprime le token
	if ((!cleaned || cleaned[0] == '\0') && curr->quoted == 0)
	{
		t_token *to_delete = curr;
		curr = curr->next;
		if (!*prev)
			*tokens = to_delete->next;
		else
			(*prev)->next = to_delete->next;
		// TODO: free to_delete->value et to_delete
		return (curr);
	}

	// Split uniquement si pas de quotes simples/doubles (quoted_flag == 0)
	if (curr->quoted == 0)
	{
		new_tokens = split_tokens_by_space(cleaned, ctx->garb);
		replace_token(tokens, curr, new_tokens);
		if (new_tokens)
		{
			*prev = get_last_token(new_tokens);
			return ((*prev)->next);
		}
		else
		{
			if (!*prev)
				*tokens = curr->next;
			else
				(*prev)->next = curr->next;
			return (curr->next);
		}
	}
	else
	{
		// Pour tokens entre quotes, on ne split pas, on remplace simplement la valeur
		// free(curr->value); // ou gestion garbage collector
		curr->value = cleaned;
		*prev = curr;
		return (curr->next);
	}
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
