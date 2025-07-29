/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:29:03 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 15:52:44 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void add_token(t_token **list, t_token *new_tok)
{
    if (!*list)
        *list = new_tok;
    else {
        t_token *tmp = *list;
        while (tmp->next)
            tmp = tmp->next; 
        tmp->next = new_tok;
    }
}
t_token	*new_token_0(char *value, type_token type, garbage **garb)
{
	t_token	*tok;

	tok = ft_malloc(garb, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = ft_strdup(value, garb);
	tok->type = type;
	tok->join = 0;
	tok->quoted = 0;
    tok->double_quote = 0;
	tok->next = NULL;
	return (tok);
}