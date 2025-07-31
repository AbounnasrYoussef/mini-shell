/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:19:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 18:15:06 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*copy_until_pipe(t_token *start,
		t_token **next_start, t_garbage **garb)
{
	t_token	*curr;
	t_token	*copy;
	t_token	**last;
	t_token	*new;

	curr = start;
	copy = NULL;
	last = &copy;
	while (curr && curr->type != PIPE)
	{
		new = ft_malloc(garb, sizeof(t_token));
		new->type = curr->type;
		new->value = ft_strdup(curr->value, garb);
		new->next = NULL;
		*last = new;
		last = &new->next;
		curr = curr->next;
	}
	if (curr && curr->type == PIPE)
		curr = curr->next;
	*next_start = curr;
	return (copy);
}

t_exec	*parse_tokens_to_exec_list(t_token *tokens, t_garbage **garb)
{
	t_exec	*head;
	t_exec	**current;
	t_token	*segment;
	t_exec	*cmd;

	head = NULL;
	current = &head;
	while (tokens)
	{
		segment = copy_until_pipe(tokens, &tokens, garb);
		cmd = ft_malloc(garb, sizeof(t_exec));
		cmd->cmd = extract_cmd_from_tokens(segment, garb);
		cmd->files = extract_redirs_from_tokens(segment, garb);
		cmd->next = NULL;
		*current = cmd;
		current = &cmd->next;
	}
	return (head);
}
