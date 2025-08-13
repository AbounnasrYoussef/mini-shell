/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:26:22 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/13 22:33:19 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// static int	count_cmd_args(t_token *tokens)
// {
// 	int		count;
// 	t_token	*tmp;
// 	t_token	*prev;

// 	count = 0;
// 	tmp = tokens;
// 	prev = NULL;
// 	while (tmp)
// 	{
// 		if (tmp->type == WORD && (!prev || !is_redirection(prev->type)))
// 			count++;
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}
// 	return (count);
// }

// char	**extract_cmd_from_tokens(t_token *tokens, t_garbage **garb)
// {
// 	char		**cmd;
// 	int			i;
// 	t_token		*tmp;
// 	t_token		*prev;

// 	cmd = ft_malloc(garb, sizeof(char *) * (count_cmd_args(tokens) + 1));
// 	if (!cmd)
// 		return (NULL);
// 	i = 0;
// 	tmp = tokens;
// 	prev = NULL;
// 	while (tmp)
// 	{
// 		if (tmp->type == WORD && (!prev || !is_redirection(prev->type)))
// 			cmd[i++] = ft_strdup(tmp->value, garb);
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}
// 	cmd[i] = NULL;
// 	return (cmd);
// }


char **extract_cmd_from_tokens(t_token *segment, t_garbage **garb)
{
    char **cmd;
    int count = 0;
    t_token *tmp = segment;

    // Comptage
    while (tmp)
    {
        if (tmp->type == WORD && tmp->value
            && (tmp->value[0] != '\0' || tmp->quoted))
            count++;
        tmp = tmp->next;
    }

    cmd = ft_malloc(garb, sizeof(char *) * (count + 1));

    // Remplissage
    count = 0;
    tmp = segment;
    while (tmp)
    {
        if (tmp->type == WORD && tmp->value
            && (tmp->value[0] != '\0' || tmp->quoted))
            cmd[count++] = tmp->value;
        tmp = tmp->next;
    }
    cmd[count] = NULL;

    return cmd;
}

