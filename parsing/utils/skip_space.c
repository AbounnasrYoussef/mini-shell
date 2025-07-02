/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:24:22 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/02 14:56:30 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int skip_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n')
        return 1;
    return 0;
}

int is_quote(char c)
{
    if (c=='\'' || c == '"')
        return 1;
    return 0;
}

int is_operator(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return 1;
    return 0;
}
int redirection(char c)
{
    if (c == '>')
        return RDR_OUT;
    else if (c == '<')
        return RDR_IN;
    return 0;
}