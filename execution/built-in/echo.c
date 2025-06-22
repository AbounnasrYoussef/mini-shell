/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:17:33 by arahhab           #+#    #+#             */
/*   Updated: 2025/06/22 18:10:55 by arahhab          ###   ########.fr       */
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
	if(str == NULL)
		return 1;
	if (ft_strcmp(str, "echo") == 0)
	{
			return 0;
	}
	return 1;
}

int trait_cmd2(char *str)
{
	int i;
	
	i = 0;
	if (ft_strcmp(str, "-n") == 0)
	{
		return 0;
	}
	
	else if(str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while(str[i] != '\0')
		{
			if(str[i] != 'n')
			{
				return 1;
			}
			i++;
		}
		return 0;
	}
	return 1;
}

void ft_echo(char **str)
{		
	int i;

	i = 0;
	printf("{%d  %d}\n", trait_cmd1(str[1]),trait_cmd2(str[2]));
	if (trait_cmd1(str[1]) == 0 && trait_cmd2(str[2]) == 0)
	{
		i = 3;
		//while(str[i] != NULL)
		//{ech
	
		ft_put_string(str[3]);
		//	i++;
		//}
	}
	else if (trait_cmd1(str[1]) == 0 && trait_cmd1(str[2]) == 1)
	{
		i = 2;
		//while(str[++i] != NULL)
		//{
			ft_put_string(str[i]);
			ft_put_string("\n");
		//	i++;
		//}
	}
	else
	{
		write(1, "\n", 1);
	}
}

int main (int argc, char **argv)
{
	//while (1)
	//{
		//char *line = readline("minishell: ");
		//ft_echo(line);
		
	//}

	ft_echo(argv);
	return 0;
}