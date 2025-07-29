/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:22:24 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 15:52:38 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void handle_single_operator(const char *line, int *i, t_token **tokens , garbage **garb)
{
    char op[2] = {line[*i], '\0'};   
    add_token(tokens, new_token_0(ft_strdup(op, garb), get_token_type(op), garb));
    (*i)++;                         
}

void handel_double_operator(const char *line ,int *i , t_token **tokens, garbage **garb)
{
    char op[3] = {line[*i], line[*i + 1], '\0'};
    add_token(tokens, new_token_0(ft_strdup(op ,  garb), get_token_type(op), garb));
    *i += 2;
}

void handel_quote(const char *line , int  *i , t_token **token ,garbage **garb)
{
    char quote;
    int start;
    
    start = *i;
    quote =  line[(*i)++];
    while (line[*i] && line[*i] != quote)
    {
        (*i)++;
    }
    (*i)++;
    char *quoted = ft_substr(line , start , *i - start , garb);
    add_token(token , new_token_0(quoted , WORD,garb));
}
