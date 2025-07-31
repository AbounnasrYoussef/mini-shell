/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:59:42 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 09:03:13 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	error_pipe(char *caracter, int *i)
// {
// 	(*i)++;
// 	if (caracter[0] == '|')
// 	{
// 		write(2, "minishell: syntax error\n", 25);
// 		return (-1);
// 	}
// 	while (caracter[*i] && skip_space(caracter[*i]))
// 		(*i)++;
// 	if (!caracter[*i] || caracter[*i] == '|'
// 		|| caracter[*i] == '<' || caracter[*i] == '>')
// 	{
// 		write(2, "minishell: syntax error\n", 25);
// 		return (-1);
// 	}
// 	return (1);
// }


int	error_pipe(char *caracter, int *i)
{
	(*i)++;

	// Skip espaces après le pipe
	while (caracter[*i] && skip_space(caracter[*i]))
		(*i)++;

	// Si rien après le pipe → erreur
	if (!caracter[*i] || caracter[*i] == '|')
	{
		write(2, "minishell: syntax error\n", 25);
		return (-1);
	}

	// Si c’est une redirection, vérifier qu’il y a bien quelque chose après
	if (caracter[*i] == '<' || caracter[*i] == '>')
	{
		int tmp = *i;

		// Passer >> ou <<
		if (caracter[tmp + 1] == caracter[tmp])
			tmp++;

		tmp++; // passer l’opérateur

		// Skip espaces
		while (caracter[tmp] && skip_space(caracter[tmp]))
			tmp++;

		// Si rien après → erreur
		if (!caracter[tmp] || caracter[tmp] == '|' || caracter[tmp] == '<' || caracter[tmp] == '>')
		{
			write(2, "minishell: syntax error\n", 25);
			return (-1);
		}
	}

	return (1);
}
