/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/09 11:09:28 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token *process_token(t_token *curr, t_token **tokens, t_token **prev, t_expand_ctx *ctx)
{
    char *expanded;
    t_token *new_tokens;

    // Si le token précédent est une redirection, on ne fait pas d’expansion ici
    if (*prev && ((*prev)->type == RDR_IN || (*prev)->type == RDR_OUT
        || (*prev)->type == APPEND || (*prev)->type == HERE_DOC))
    {
        *prev = curr;
        return (curr->next);
    }

    if (curr->quoted == 1)
    {
        // Pas d’expansion si token entre quotes simples/doubles
        *prev = curr;
        return (curr->next);
    }

    expanded = expand_token(curr->value, ctx->exit_code, ctx->env, ctx->garb);
    if (!expanded)
        expanded = ft_strdup("", ctx->garb);

    // Supprime les quotes si présentes (optionnel selon ta logique)
    char *cleaned = ft_strtrim_custom(expanded, ctx->garb, 0);

    // Si chaîne vide et non quote, supprime le token
    if (!cleaned || cleaned[0] == '\0')
    {
        t_token *to_delete = curr;
        curr = curr->next;
        if (!*prev)
            *tokens = to_delete->next;
        else
            (*prev)->next = to_delete->next;
        // ici tu dois free to_delete->value et to_delete lui-même si nécessaire
        return (curr);
    }

    // Split la chaîne étendue en tokens (pour gérer "ls -la" -> "ls" et "-la")
    new_tokens = split_tokens_by_space(cleaned, ctx->garb);

    // Remplace le token initial par la liste des tokens splittés
    replace_token(tokens, curr, new_tokens);

    // Comme curr est remplacé, on reprend à new_tokens->next
    if (new_tokens)
    {
        *prev = get_last_token(new_tokens);
        return ((*prev)->next);
    }
    else
    {
        // new_tokens est NULL, on supprime curr
        if (!*prev)
            *tokens = curr->next;
        else
            (*prev)->next = curr->next;
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
