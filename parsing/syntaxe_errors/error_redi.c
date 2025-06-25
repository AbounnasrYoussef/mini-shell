/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:17:40 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/25 14:27:54 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int printf_error()
{
	write(2, "minishell: syntax error\n", 25);
    return (-1);
}


static int	check_redir_target(char *str, int *i)
{
	char	quote;

	if (str[*i] == '"' || str[*i] == '\'')
	{
		quote = str[(*i)++];
		while (str[*i] && str[*i] != quote)
			(*i)++;
		if (str[*i] != quote)
			printf_error();

		(*i)++;
		return (1);
	}
	if (!str[*i])
        printf_error();
	if (str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
        printf_error();
	return (1);
}

int	error_redir(char *str, int *i)
{
	if ((str[*i] == '>' && str[*i + 1] == '>') ||
		(str[*i] == '<' && str[*i + 1] == '<'))
		(*i) += 2;
	else
		(*i)++;
	while (str[*i] && skip_space(str[*i]))
		(*i)++;
	return (check_redir_target(str, i));
}
