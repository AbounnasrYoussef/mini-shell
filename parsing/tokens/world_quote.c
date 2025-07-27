/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:41:47 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/27 10:27:19 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_word(const char *line, int *i, t_token **tokens, garbage **garb)
{
    char *res = ft_strdup("", garb);

    while (line[*i] && !skip_space(line[*i]) && !is_operator(line[*i]))
    {
        if (line[*i] == '\'' || line[*i] == '"')
        {
            char quote = line[*i];
            (*i)++;  // skip opening quote
            int q_start = *i;
            while (line[*i] && line[*i] != quote)
                (*i)++;
            char *quoted_part = ft_substr(line, q_start, *i - q_start, garb);
            res = ft_strjoin(res, quoted_part, garb);
            if (line[*i] == quote)
                (*i)++;  // skip closing quote
        }
        else
        {
            int w_start = *i;
            while (line[*i] && !skip_space(line[*i]) && !is_operator(line[*i]) &&
                   line[*i] != '\'' && line[*i] != '"')
                (*i)++;
            char *part = ft_substr(line, w_start, *i - w_start, garb);
            res = ft_strjoin(res, part, garb);
        }
    }
    add_token(tokens, new_token(res, WORD, garb));
}


