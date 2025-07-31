/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:27:22 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 18:15:12 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirection(type_token type)
{
	return (type == RDR_IN || type == RDR_OUT
		|| type == APPEND || type == HERE_DOC);
}

t_file	*extract_redirs_from_tokens(t_token *tokens, t_garbage **garb)
{
	t_file	*head;
	t_file	**current;
	t_file	*f;

	head = NULL;
	current = &head;
	while (tokens)
	{
		if (is_redirection(tokens->type) && tokens->next)
		{
			f = ft_malloc(garb, sizeof(t_file));
			f->type = tokens->type;
			f->file_name = ft_strdup(tokens->next->value, garb);
			f->next = NULL;
			*current = f;
			current = &f->next;
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (head);
}
