/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:26:22 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 17:59:27 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **extract_cmd_from_tokens(t_token *tokens, garbage **garb)
{
    int count = 0;
    t_token *tmp = tokens;
    t_token *prev = NULL;

    while (tmp)
    {
        if (tmp->type == WORD)
        {
            if (!prev || !is_redirection(prev->type))
                count++;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    char **cmd = ft_malloc(garb, sizeof(char *) * (count + 1));
    tmp = tokens;
    prev = NULL;
    int i = 0;

    while (tmp)
    {
        if (tmp->type == WORD)
        {
            if (!prev || !is_redirection(prev->type))
                cmd[i++] = ft_strdup(tmp->value, garb);
        }
        prev = tmp;
        tmp = tmp->next;
    }
    cmd[i] = NULL;
    return cmd;
}



