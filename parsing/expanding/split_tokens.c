/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:37:21 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/24 18:54:13 by yabounna         ###   ########.fr       */
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
t_token	*split_into_tokens(char *str, garbage **garb)
{
	char	**words ;
    words = ft_split(str, ' ', garb);
	t_token	*head = NULL;
	t_token	*new;
	int		i = 0;

	while (words && words[i])
	{
		new = new_token(words[i], WORD, garb);
		add_token_back(&head, new);
		i++;
	}
	return (head);
}
