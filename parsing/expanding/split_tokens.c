/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:37:21 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 18:11:28 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

t_token	*get_last_token(t_token *tokens)
{
	while (tokens && tokens->next)
		tokens = tokens->next;
	return (tokens);
}

t_token	*split_by_space(char *str, t_garbage **garb)
{
	t_token	*head;
	t_token	*new;
	char	**words;
	int		i;

	head = NULL;
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

t_token	*handle_quoted_string(char *str, t_garbage **garb)
{
	t_token	*head;
	t_token	*new;
	char	*trimmed;

	head = NULL;
	trimmed = ft_substr(str, 1, ft_strlen(str) - 2, garb);
	if (!trimmed)
		return (NULL);
	new = new_token_0(trimmed, WORD, garb);
	new->quoted = 1;
	add_token_back(&head, new);
	return (head);
}

t_token	*split_into_tokens(char *str, t_garbage **garb)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (handle_quoted_string(str, garb));
	else
		return (split_by_space(str, garb));
}
