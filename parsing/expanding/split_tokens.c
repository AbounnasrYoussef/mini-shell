/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:37:21 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 11:40:07 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Remplace un token par une liste
void	replace_token(t_token **head, t_token *old, t_token *new_list)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*last;

	prev = NULL;
	curr = *head;
	while (curr && curr != old)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
		*head = new_list;
	else
		prev->next = new_list;
	last = new_list;
	while (last && last->next)
		last = last->next;
	if (last)
		last->next = old->next;
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
	t_token	*head;
	t_token	*new;
	char	**words;
	int		i;
	size_t	len;

	head = NULL;
	len = ft_strlen(str);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
	{
		char *trimmed = ft_substr(str, 1, len - 2, garb);
		if (!trimmed)
			return (NULL);
		new = new_token_0(trimmed, WORD, garb);
		new->quoted = 1;
		add_token_back(&head, new);
		return (head);
	}
	words = ft_split(str, ' ', garb);
	i = 0;
	while (words && words[i])
	{
		new = new_token_0(words[i], WORD, garb);
		new->quoted = 0;
		add_token_back(&head, new);
		i++;
	}
	return (head);
}



