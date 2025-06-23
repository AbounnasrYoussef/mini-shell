/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:17:33 by arahhab           #+#    #+#             */
/*   Updated: 2025/06/23 17:19:58 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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

void ft_echo(int argc, char **str)
{		
	int i;

	i = 0;
	

	if (argc > 2)
	{
		//printf("{%d  %d}\n", trait_cmd1(str[1]),trait_cmd2(str[2]));
		if (trait_cmd1(str[1]) == 0)
		{
			if (trait_cmd2(str[2]) == 0)
			{
				i = 3;
				while (str[i] != NULL && trait_cmd2(str[i]) == 0)
				{
					i++;
				}
				while(str[i] != NULL)
				{
					ft_put_string(str[i]);
					if (str[i+1] != NULL)
						ft_put_string(" ");
					i++;
				}
			}
			else if (trait_cmd2(str[2]) == 1)
			{
				i = 2;
				while(str[i] != NULL)
				{
					ft_put_string(str[i]);
					if (str[i+1] != NULL)
						ft_put_string(" ");
					i++;
				}
				ft_put_string("\n");
			}
		}
				
	}
	else if (argc == 2 && trait_cmd1(str[1]) == 0)
	{
		//printf("{%d}\n", trait_cmd1(str[1]));
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

	ft_echo(argc, argv);
	return 0;
}