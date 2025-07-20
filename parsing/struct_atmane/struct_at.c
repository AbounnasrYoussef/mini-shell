/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:19:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/20 11:00:30 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token *copy_until_pipe(t_token *start, t_token **next_start,garbage **garb)
{
	t_token *curr = start;
	t_token *copy = NULL;
	t_token **last = &copy;

	while (curr && curr->type != PIPE)
	{
		t_token *new = ft_malloc(garb, sizeof(t_token));
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
	return copy;
}

t_exec	*parse_tokens_to_exec_list(t_token *tokens, garbage **garb)
{
	t_exec *head = NULL; // initiliaser lbedia dial la liste
	t_exec **current = &head; // pointeur vers dakchi li jay

	while (tokens)
	{
		t_token *segment;// variables temporaire bach nsstokiwe  group dial tokens
		segment = copy_until_pipe(tokens, &tokens , garb);

		t_exec *cmd = ft_malloc(garb ,sizeof(t_exec));
		cmd->cmd = extract_cmd_from_tokens(segment, garb);
		cmd->files = extract_redirs_from_tokens(segment, garb);
		cmd->next = NULL;

		*current = cmd;
		current = &cmd->next;
	}
	return head;
}
