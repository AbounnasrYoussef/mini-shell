/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:44:25 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 15:42:17 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// hade fonction hiya li k determiner lina type dial token
type_token get_token_type(char *str) {
    if (!ft_strcmp(str, "|"))
        return PIPE;
    if (!ft_strcmp(str, "<"))
        return RDR_IN;
    if (!ft_strcmp(str, "<<"))
        return HERE_DOC;
    if (!ft_strcmp(str, ">"))
        return RDR_OUT;
    if (!ft_strcmp(str, ">>"))
        return APPEND;
    return WORD;
}

t_token *tokens(const char *line, garbage **garb)
{
    t_token *tokens = NULL;
    int i = 0;
    
    while (line[i] != '\0')
    {
        space_skip(line , &i);
        if (!line[i])
            break;
        if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i])
            handel_double_operator(line , &i , &tokens,garb);
        else if (is_operator(line[i]))
            handle_single_operator(line , &i , &tokens,garb);
        else
            handle_word(line, &i , &tokens,garb);  // <-- TOUJOURS ici, même pour les quotes
    }
    return tokens;
}
