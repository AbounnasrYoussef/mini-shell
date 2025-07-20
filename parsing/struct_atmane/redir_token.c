/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:27:22 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/20 11:03:00 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static t_file	*create_file(int type, char *filename, garbage **garb)
{
	t_file *new = ft_malloc(garb,sizeof(t_file));
	new->type = type;
	new->file_name = ft_strdup(filename, garb);
	new->next = NULL;
	return new;
}


t_file	*extract_redirs_from_tokens(t_token *tokens, garbage **garb)
{
	t_file *head = NULL;
	t_file **current = &head;

	while (tokens && tokens->next)
	{
		if (tokens->type == RDR_IN || tokens->type == RDR_OUT
			|| tokens->type == APPEND || tokens->type == HERE_DOC)
		{
			t_file *file = create_file(tokens->type, tokens->next->value, garb);
			*current = file;
			current = &file->next;
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return head;
}
