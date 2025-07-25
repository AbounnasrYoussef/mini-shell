/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:37:21 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/25 09:40:56 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// Remplace un token par une liste
void	replace_token(t_token **head, t_token *old, t_token *new_list)
{
	t_token	*prev = NULL;
	t_token	*current = *head;

	while (current && current != old)
	{
		prev = current;
		current = current->next;
	}
	if (!prev)
		*head = new_list;
	else
		prev->next = new_list;
}

// Renvoie le dernier token d'une liste
t_token	*get_last_token(t_token *tokens)
{
	while (tokens && tokens->next)
		tokens = tokens->next;
	return (tokens);
}

// Split une string expandée en tokens (type WORD)
t_token *split_into_tokens(char *str, garbage **garb)
{
    t_token *head = NULL;
    t_token *new;
    char **words;
    int i = 0;
    size_t len;

    len = ft_strlen(str);

    // Si la chaîne commence ET finit par des doubles quotes, on ne split pas
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
    {
        // on enlève les quotes externes
        char *trimmed = ft_substr(str, 1, len - 2, garb);
        if (!trimmed)
            return (NULL);
        new = new_token(trimmed, WORD, garb);
        // marquer le token comme quoted si tu veux
        new->quoted = 1;
        add_token_back(&head, new);
        return (head);
    }

    // Sinon on split normalement
    words = ft_split(str, ' ', garb);
    while (words && words[i])
    {
        new = new_token(words[i], WORD, garb);
        new->quoted = 0;
        add_token_back(&head, new);
        i++;
    }
    return (head);
}



