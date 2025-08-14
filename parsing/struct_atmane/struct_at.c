/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:19:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/14 21:08:29 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_redirection(type_token type)
{
    return (type == RDR_IN || type == RDR_OUT
        || type == APPEND || type == HERE_DOC);
}

t_exec *parse_tokens_to_exec_list(t_token *tokens, t_garbage **garb)
{
    t_exec *head;
    t_exec *cmd;
    t_file  **current;
    t_file  *f;
    t_exec *new_cmd;
    int i;

    cmd = NULL;
    head = NULL;
    while (tokens != NULL)
    {
        new_cmd = ft_malloc(garb, sizeof(t_exec));
        new_cmd->cmd = ft_malloc(garb, 2000 * sizeof(char *));
        i = 0;
        new_cmd->files = NULL;
        new_cmd->next = NULL;
        current = &(new_cmd->files);
        if (!head)
        {
            head = new_cmd;
            cmd = new_cmd;
        }
        else
        {
            cmd->next = new_cmd;
            cmd = new_cmd;
        }
        while (tokens != NULL && tokens->type != PIPE)
        {
            if (tokens->value != NULL)
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
                else
                {
                    new_cmd->cmd[i] = tokens->value;
                    i++;
                }
            }
            tokens = tokens->next;
        }
        new_cmd->cmd[i] = NULL;

        if (tokens != NULL && tokens->type == PIPE)
            tokens = tokens->next;
    }
    return head;
}

