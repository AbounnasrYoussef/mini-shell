/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:59:42 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/08 12:51:38 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// static int	print_err(void)
// {
// 	write(2, "minishell: syntax error\n", 25);
// 	ft_exit_status(258, 1);
// 	return (-1);
// }

// int	error_pipe(char *caracter, int *i)
// {
// 	int	tmp;

// 	(*i)++;
// 	while (caracter[*i] && skip_space(caracter[*i]))
// 		(*i)++;
// 	if (!caracter[*i] || caracter[*i] == '|')
// 		print_err();
// 	if (caracter[*i] == '<' || caracter[*i] == '>')
// 	{
// 		tmp = *i;
// 		if (caracter[tmp + 1] == caracter[tmp])
// 			tmp++;
// 		tmp++;
// 		while (caracter[tmp] && skip_space(caracter[tmp]))
// 			tmp++;
// 		if (!caracter[tmp] || caracter[tmp] == '|'
// 			|| caracter[tmp] == '<' || caracter[tmp] == '>')
// 			print_err();
// 	}
// 	return (1);
// }

static int	print_err(void)
{
	write(2, "minishell: syntax error\n", 25);
	ft_exit_status(258, 1);
	return (-1);
}

int	error_pipe(char *line, int *i)
{
	int	tmp;

	(*i)++;
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	if (!line[*i] || line[*i] == '|')
		return (print_err());
	if (line[*i] == '<' || line[*i] == '>')
	{
		tmp = *i;
		if (line[tmp + 1] == line[tmp])
			tmp++;
		tmp++;
		while (line[tmp] && (line[tmp] == ' ' || line[tmp] == '\t'))
			tmp++;
		if (!line[tmp] || line[tmp] == '|' || line[tmp] == '<'
			|| line[tmp] == '>')
			return (print_err());
	}
	return (1);
}
