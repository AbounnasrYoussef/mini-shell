/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:00:14 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 15:40:09 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	error_quote(char *caracter, int *i)
{
	char	quote;

	while (caracter[*i] != '\0')
	{
		if (caracter[*i] == '\'' || caracter[*i] == '\"')
		{
			quote = caracter[(*i)++];
			while (caracter[*i] != '\0' && caracter[*i] != quote)
				(*i)++;
			if (!caracter[*i])
			{
				write(2, "minishell: syntax error\n", 25);
				return (-1);
			}
		}
		(*i)++;
	}
	return (1);
}
