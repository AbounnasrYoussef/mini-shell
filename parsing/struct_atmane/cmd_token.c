/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:26:22 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/20 10:26:53 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int	count_words(t_token *tokens)
{
	int count = 0;

	while (tokens)
	{
		if (tokens->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return count;
}

char	**extract_cmd_from_tokens(t_token *tokens, garbage **garb)
{
	int		i = 0;
	int		size = count_words(tokens);
	char	**cmd = ft_malloc(garb,sizeof(char *) * (size + 1));

	while (tokens)
	{
		if (tokens->type == WORD)
		{
			cmd[i] = ft_strdup(tokens->value, garb);
			i++;
		}
		tokens = tokens->next;
	}
	cmd[i] = NULL;
	return cmd;
}
