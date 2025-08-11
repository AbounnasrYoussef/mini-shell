/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/11 15:31:24 by yabounna         ###   ########.fr       */
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
			while (value[i] == '$')
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


// static t_token	*process_token(t_token *curr, t_token **tokens,
// 						t_token **prev, t_expand_ctx *ctx, t_parsing_context ctxu)
// {
// 	char		*expanded = NULL;
// 	t_token		*new_tokens;

// 	// On ne fait pas d'expansion pour les tokens après redirections
// 	if (*prev && ((*prev)->type == RDR_IN || (*prev)->type == RDR_OUT
// 		|| (*prev)->type == APPEND || (*prev)->type == HERE_DOC))
// 	{
// 		*prev = curr;
// 		return (curr->next);
// 	}
// 	// printf("%d\n\n\n\n", ctxu.quoted_flag );
// 	// Si simple quotes (quoted_flag == 2), on ne fait aucune expansion, juste dupliquer
// 	if (ctxu.quoted_flag == 2)
// 	{
// 		// printf("%d\n\n\n\n", curr->quoted );
// 		*prev = curr;
// 		return (curr->next);
// 	}

// 	// Si double quotes (quoted_flag == 1), expansion spécifique (respect des règles dans "")
// 	if (ctxu.quoted_flag == 1){
// 		expanded = expand_token_double_quotes(curr->value, ctx->exit_code, ctx->env, ctx->garb);
// 	}
// 	else
// 		// Sinon expansion normale (pas de quotes)
// 		expanded = expand_token(curr->value, ctx->exit_code, ctx->env, ctx->garb);
	
// 	if (!expanded)
// 		expanded = ft_strdup("", ctx->garb);

// 	// Suppression optionnelle des quotes (selon comportement voulu)
// 	char *cleaned = ft_strtrim_custom(expanded, ctx->garb, curr->quoted);

// 	// Si résultat vide et pas de quotes, on supprime le token
	
// 	if ((!cleaned || cleaned[0] == '\0') && curr->quoted == 0)
// 	{
// 		t_token *to_delete = curr;
// 		curr = curr->next;
// 		if (!*prev)
// 			*tokens = to_delete->next;
// 		else
// 			(*prev)->next = to_delete->next;
// 		// TODO: free to_delete->value et to_delete
// 		return (curr);
// 	}
// 	// Split uniquement si pas de quotes simples/doubles (quoted_flag == 0)
	
// 	if (curr->quoted == 0)
// 	{
		
// 		new_tokens = split_tokens_by_space(cleaned, ctx->garb);
// 		replace_token(tokens, curr, new_tokens);
		
// 		if (new_tokens)
// 		{
// 			*prev = get_last_token(new_tokens);
// 			return ((*prev)->next);
// 		}
// 		else
// 		{
// 			if (!*prev)
// 				*tokens = curr->next;
// 			else
// 				(*prev)->next = curr->next;
// 			return (curr->next);
// 		}
		
// 	}
// 	else
// 	{
// 		// Pour tokens entre quotes, on ne split pas, on remplace simplement la valeur
// 		// free(curr->value); // ou gestion garbage collector
		
// 		curr->value = cleaned;
// 		*prev = curr;
// 		return (curr->next);
// 	}
	
// }


// void	expand_all_tokens(t_token **tokens, int exit_code
// 		, t_list_env *env, t_parsing_context ctx)
// {
// 	t_token			*curr;
// 	t_token			*prev;
// 	t_expand_ctx	ctx1;

// 	curr = *tokens;
// 	prev = NULL;
// 	ctx1.exit_code = exit_code;
// 	ctx1.env = env;
// 	ctx1.garb = ctx.garb;
	
// 	while (curr)
// 	{
// 		// curr = process_token(curr, tokens, &prev, &ctx1, ctx);
// 		if (ctx.quoted_flag == 1){
// 			curr->value = expand_token_double_quotes(curr->value, ctx1.exit_code, ctx1.env, ctx1.garb);
// 		}
// 		else
// 		{
			
// 		}
// 		curr =  curr->next;
// 	}
// }

static int	should_expand(t_token *curr, t_parsing_context ctx)
{
	if (ctx.quoted_flag == 2) 
	{
		// printf("yyyy\n");
		return (0);
	}// simple quotes
	if (ctx.quoted_flag == 1) // double quotes
	{
		// printf("nnn\n");
		return (1);
		
	}
	if (curr->value[0] == '$' && curr->value[1] == '"')
	{
		// printf("gggg\n");
		return (0);
		
	}
	return (1);
}


static char	*expand_value(t_token *curr, t_expand_ctx *ctx1,
		t_parsing_context ctx)
{
	if (ctx.quoted_flag == 1)
	{
		// printf("youssef");
		return (expand_token_double_quotes(
			curr->value, ctx1->exit_code, ctx1->env, ctx1->garb));
		
	}
	return (expand_token(
		curr->value, ctx1->exit_code, ctx1->env, ctx1->garb));
}


void	expand_all_tokens(t_token **tokens, int exit_code,
		t_list_env *env, t_parsing_context ctx)
{
	t_token			*curr;
	t_expand_ctx	ctx1;

	curr = *tokens;
	ctx1.exit_code = exit_code;
	ctx1.env = env;
	ctx1.garb = ctx.garb;
	while (curr)
	{
		if (!should_expand(curr, ctx))
		{
			curr = curr->next;
			continue ;
		}
		curr->value = expand_value(curr, &ctx1, ctx);
		curr = curr->next;
	}
}
