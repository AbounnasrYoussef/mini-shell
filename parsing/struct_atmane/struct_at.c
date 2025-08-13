/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:19:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/13 22:33:32 by yabounna         ###   ########.fr       */
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

static void	add_exec_node(t_exec **current, t_token *segment, t_garbage **garb)
{
	t_exec	*cmd;

	cmd = ft_malloc(garb, sizeof(t_exec));
	cmd->cmd = extract_cmd_from_tokens(segment, garb);
	cmd->files = extract_redirs_from_tokens(segment, garb);
	cmd->next = NULL;
	*current = cmd;
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
			add_exec_node(current, segment, garb);
			current = &((*current)->next);
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

// t_exec	*parse_tokens_to_exec_list(t_token *tokens, t_garbage **garb)
// {
// 	t_exec	*head;
// 	t_exec	*cmd;
// 	int		i;

// 	cmd = ft_malloc(garb, sizeof(t_exec));
// 	head = cmd;
// 	i = 0;
// 	cmd->cmd = malloc(2000 * sizeof(char *));
// 	while (tokens != NULL)
// 	{
// 		if (tokens && tokens->type == PIPE)
// 		{
// 			cmd->cmd = malloc(2000 * sizeof(char *));
// 			if (tokens->next != NULL)
// 			{
// 				tokens = tokens->next;
// 				cmd = cmd->next;
// 				continue ;
// 			}
// 		}
// 		if (tokens->value != NULL)
// 		{
// 			cmd->cmd[i] = (tokens)->value;
// 			cmd->files = extract_redirs_from_tokens(tokens, garb);
// 			i++;
// 		}
// 		else
// 		{
// 			cmd->cmd[i] = (tokens)->value;
// 			cmd->files = NULL;
// 			i++;	
// 		}
// 		cmd->cmd[i] = NULL;
// 		tokens = tokens->next;
// 	}
// 	cmd->next = NULL;
	
// 	printf("'%s'\n\n", head->cmd[0]);
// 	printf("'%s'\n\n", head->next->cmd[0]);
// 	return (head);
// }