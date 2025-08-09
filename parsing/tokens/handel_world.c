/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:38:19 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/09 12:21:30 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*new_token(char *value, type_token type, int i, t_garbage **garb)
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

void	handle_quoted_part(const char *line, int *i,
			char **res, int *quoted_flag, t_garbage **garb)
{
	char	quote;
	int		start;
	char	*substr;

	quote = line[*i];
	(*i)++;
	start = *i;

	// On lit jusqu’à la quote fermante ou fin de ligne
	while (line[*i] && line[*i] != quote)
		(*i)++;

	// On extrait la partie entre quotes
	substr = ft_substr(line, start, *i - start, garb);
	*res = ft_strjoin(*res, substr, garb);

	// On définit le flag selon le type de quote
	if (quote == '\'')
		*quoted_flag = 2;  // 2 = simple quotes, aucune expansion plus tard
	else if (quote == '"')
		*quoted_flag = 1;  // 1 = double quotes, expansion possible

	// Si on est bien sur une quote fermante, on avance
	if (line[*i] == quote)
		(*i)++;
}

void	handle_word(const char *line, int *i,
			t_token **tokens, t_garbage **garb)
{
	char	*res;
	char	*word;
	int		start;
	int		quoted_flag;

	quoted_flag = 0; // 0 = pas de quotes, expansion normale possible
	res = ft_strdup("", garb);

	while (line[*i] && !skip_space(line[*i]) && !is_operator(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			// Gérer les quotes, concaténer dans res et set flag
			handle_quoted_part(line, i, &res, &quoted_flag, garb);
		}
		else
		{
			// Partie normale hors quotes
			start = *i;
			while (line[*i] && !skip_space(line[*i])
				&& !is_operator(line[*i])
				&& line[*i] != '\'' && line[*i] != '"')
				(*i)++;

			word = ft_substr(line, start, *i - start, garb);
			res = ft_strjoin(res, word, garb);
		}
	}

	if (res)
		add_token(tokens, new_token(res, WORD, quoted_flag, garb));
}


