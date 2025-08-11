/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:44:25 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/10 15:54:18 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

type_token	get_token_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	if (!ft_strcmp(str, "<"))
		return (RDR_IN);
	if (!ft_strcmp(str, "<<"))
		return (HERE_DOC);
	if (!ft_strcmp(str, ">"))
		return (RDR_OUT);
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	return (WORD);
}

void print_tokens(t_token *tokens)
{
	while (tokens != NULL)
	{
		printf("%s----\n\n", tokens->value);
		tokens = tokens->next;
	}
}
t_token	*tokens(const char *line, t_garbage **garb, t_parsing_context	*ctx)
{
	t_token				*tokens;
	int					i;

	tokens = NULL;
	i = 0;
	(*ctx).line = line;
	(*ctx).index = &i;
	(*ctx).garb = garb;
	while (line[i] != '\0')
	{
		space_skip(line, &i);
		if (!line[i])
			break ;
		if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i])
			handel_double_operator(line, &i, &tokens, garb);
		else if (is_operator(line[i]))
			handle_single_operator(line, &i, &tokens, garb);
		else
			handle_word(ctx, &tokens);
	}
	return (tokens);
}
