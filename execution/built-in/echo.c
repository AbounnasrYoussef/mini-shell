/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:17:33 by arahhab           #+#    #+#             */
/*   Updated: 2025/06/19 23:53:29 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int trait_char(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == "$")
			return 1;
		else if(str[i] == "\\")
			return 2;
		i++;
	}
	return 3;
}

int trait_cmd1(char *str)
{
	if (ft_strcmp(str, "echo"))
	{
			return 0;
	}
	return 1;
}

int trait_cmd2(char *str)
{
	if (ft_strcmp(str, "-n"))
	{
			return 0;
	}
	return 1;
}

void ft_echo(char **str)
{
	if (trait_cmd1(str[0]) == 0 && trait_cmd1(str[1]) == 0)
	{
		
	}
	else if (trait_cmd1(str[0]) == 0 && trait_cmd1(str[1]) == 1)
	{
		
	}
	else
	{
		write(1, "\n", 1);
	}
}

int main (int argc, char **argv)
{
	while (1)
	{
		//char *line = readline("minishell: ");
		//ft_echo(line);
		ft_echo(argv);
	}
	return 0;
}