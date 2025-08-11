/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:37:21 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/11 21:40:21 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


t_token	*get_last_token(t_token *tokens)
{
	while (tokens && tokens->next)
		tokens = tokens->next;
	return (tokens);
}

// Fonction pour splitter une chaîne par espace en tokens (sans gestion spéciale des quotes)
t_token *split_tokens_by_space(char *str, t_garbage **garb)
{
    t_token *head = NULL;
    t_token *new_token;
    char **words;
    int i = 0;

    if (!str)
        return NULL;
    words = ft_split(str, ' ', garb);
    if (!words)
        return NULL;

    while (words[i])
    {
        if (words[i][0] != '\0') // ignore tokens vides
        {
            new_token = new_token_0(words[i], WORD, garb);
            new_token->quoted = 0;
            add_token_back(&head, new_token);
        }
        i++;
    }
    return head;
}

// Fonction qui remplace un token 'old' dans la liste *head par une liste 'new_list'
void replace_token(t_token **head, t_token *old, t_token *new_list)
{
    t_token *prev = NULL;
    t_token *curr = *head;
    t_token *last;

    while (curr && curr != old)
    {
        prev = curr;
        curr = curr->next;
    }
    if (!curr)
        return;

    if (!prev)
        *head = new_list;
    else
        prev->next = new_list;

    if (new_list)
    {
        last = new_list;
        while (last->next)
            last = last->next;
        last->next = old->next;
    }
    else
    {
        // Si new_list est NULL, on supprime juste old
        if (prev)
            prev->next = old->next;
        else
            *head = old->next;
    }
}

// Fonction principale pour gérer l'expansion et split dans les tokens
void expand_token_1(t_token **tokens_head, t_token *token_to_expand,
    t_list_env *env, t_garbage **garb)
{
    char *var_name = token_to_expand->value; // exemple : "a"
    char *expanded_value = get_env_value(var_name, env, garb);

    if (!expanded_value)
        expanded_value = ft_strdup("", garb);

    // Split l'expansion en tokens
    t_token *new_tokens = split_tokens_by_space(expanded_value, garb);

    // Remplace le token initial par la liste des tokens splittés
    replace_token(tokens_head, token_to_expand, new_tokens);
}

// Cette fonction supprime les quotes et split correctement
