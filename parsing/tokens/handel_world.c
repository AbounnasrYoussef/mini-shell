/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:38:19 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/30 17:46:55 by yabounna         ###   ########.fr       */
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
void	handle_quoted_part(const char *line, int *i, char **res, int *quoted_flag, garbage **garb)
{
	char	quote = line[*i];
	int		start;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
	{
		char *substr = ft_substr(line, start, *i - start, garb);
		*res = ft_strjoin(*res, substr, garb);
		if (quote == '\'')
			*quoted_flag = 1; // simple quote
		else if (quote == '"')
			*quoted_flag = 2; // double quote
		(*i)++;
	}
}


void	handle_word(const char *line, int *i, t_token **tokens, garbage **garb)
{
	char	*res = ft_strdup("", garb);
	int		quoted_flag = 0;

	while (line[*i] && !skip_space(line[*i]) && !is_operator(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
			handle_quoted_part(line, i, &res, &quoted_flag, garb);
		else
		{
			int	start = *i;
			while (line[*i] && !skip_space(line[*i]) && !is_operator(line[*i])
				&& line[*i] != '\'' && line[*i] != '"')
				(*i)++;
			char *word = ft_substr(line, start, *i - start, garb);
			res = ft_strjoin(res, word, garb);
		}
	}
	if (res && res[0] != '\0')
		add_token(tokens, new_token(res, WORD, quoted_flag, garb));
}

