/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:38:19 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 15:46:54 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*new_token(char *value, type_token type,int i, garbage **garb)
{
	t_token	*tok;

	tok = ft_malloc(garb, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = ft_strdup(value, garb);
	tok->type = type;
    tok->join = 1;
	tok->quoted = i;
    tok->double_quote = 0;
	tok->next = NULL;
	return (tok);
}

static void handle_quoted_part(const char *line, int *i, char **res, garbage **garb, t_token **tokens)
{
    char quote = line[*i];
    (*i)++;
    int q_start = *i;

    while (line[*i] && line[*i] != quote)
        (*i)++;
    char *quoted_part = ft_substr(line, q_start, *i - q_start, garb);
    *res = ft_strjoin(*res, quoted_part, garb);

    if (line[*i] == quote)
        (*i)++;
    if (quote == '\'')
    {
        add_token(tokens, new_token(*res, WORD, 1, garb));
        *res = NULL;
    }
}

void handle_word(const char *line, int *i, t_token **tokens, garbage **garb)
{
    char *res = ft_strdup("", garb);

    while (line[*i] && !skip_space(line[*i]) && !is_operator(line[*i]))
    {
        if (line[*i] == '\'' || line[*i] == '"')
        {
            handle_quoted_part(line, i, &res, garb, tokens);
            if (!res)
                return;
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
    if (res)
        add_token(tokens, new_token(res, WORD, 0, garb));
}
