/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:41:47 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/25 14:58:04 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_word(const char *line, int *i, t_token **tokens, garbage **garb)
{
    // int start = *i;
    char *result = ft_strdup("", garb); // mot final
    while (line[*i] && !skip_space(line[*i]) && !is_operator(line[*i]))
    {
        if (is_quote(line[*i]))
        {
            char quote = line[(*i)++];
            int q_start = *i;
            while (line[*i] && line[*i] != quote)
                (*i)++;
            char *inside = ft_substr(line, q_start, *i - q_start, garb);
            result = ft_strjoin(result, inside, garb);
            if (line[*i] == quote)
                (*i)++; // skip closing quote
        }
        else
        {
            int w_start = *i;
            while (line[*i] && !is_quote(line[*i]) && !skip_space(line[*i]) && !is_operator(line[*i]))
                (*i)++;
            char *part = ft_substr(line, w_start, *i - w_start, garb);
            result = ft_strjoin(result, part, garb);
        }
    }
    add_token(tokens, new_token(result, WORD, garb));
}
