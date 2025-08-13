/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:26:22 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/13 02:50:59 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_cmd_args(t_token *tokens)
{
	int		count;
	t_token	*tmp;
	t_token	*prev;

	count = 0;
	tmp = tokens;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type == WORD && (!prev || !is_redirection(prev->type)))
			count++;
		prev = tmp;
		tmp = tmp->next;
	}
	return (count);
}

char	**extract_cmd_from_tokens(t_token *tokens, t_garbage **garb)
{
	char		**cmd;
	int			i;
	t_token		*tmp;
	t_token		*prev;

	cmd = ft_malloc(garb, sizeof(char *) * (count_cmd_args(tokens) + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	tmp = tokens;
	prev = NULL;
	
	while (tmp)
	{
		if (tmp->type == WORD && (!prev || !is_redirection(prev->type)))
			cmd[i++] = ft_strdup(tmp->value, garb);
		prev = tmp;
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
