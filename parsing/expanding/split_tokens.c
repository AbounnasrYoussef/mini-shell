/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:37:21 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/12 10:15:25 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*get_last_token(t_token *tokens)
{
	while (tokens && tokens->next)
		tokens = tokens->next;
	return (tokens);
}

t_token *split_tokens_by_space(char *str, t_garbage **garb)
{
    t_token *head;
    t_token *new_token;
    char **words;
    
    int i = 0;
    head = NULL;
    if (!str)
        return NULL;
    words = ft_split(str, ' ', garb);
    if (!words)
        return NULL;
    while (words[i])
    {
        if (words[i][0] != '\0')
        {
            new_token = new_token_0(words[i], WORD, garb);
            new_token->quoted = 0;
            add_token_back(&head, new_token);
        }
        i++;
    }
    return (head);
}

void replace_token(t_token **head, t_token *old, t_token *new_list)
{
    t_token *prev;
    t_token *curr;
    t_token *last;

    1 && (prev = NULL , curr = *head);
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
        if (prev)
            prev->next = old->next;
        else
            *head = old->next;
    }
}

