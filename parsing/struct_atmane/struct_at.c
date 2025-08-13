/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:19:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/13 02:52:34 by arahhab          ###   ########.fr       */
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
		new->value = curr->value;
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
	segment = tokens;
	while (tokens != NULL)
	{
		if (tokens->value != NULL)
		{
			segment = copy_until_pipe(tokens, &tokens, garb);
			cmd = ft_malloc(garb, sizeof(t_exec));
			cmd->cmd = extract_cmd_from_tokens(segment, garb);
			cmd->files = extract_redirs_from_tokens(segment, garb);
			cmd->next = NULL;
			*current = cmd;
			
			current = &cmd->next;
		}
		else
		{
			cmd = ft_malloc(garb, sizeof(t_exec));
			cmd->cmd = &(tokens)->value;
			cmd->next = NULL;
			tokens = tokens->next;
		}
	}
	return (head);
}
