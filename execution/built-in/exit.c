/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:45:34 by arahhab           #+#    #+#             */
/*   Updated: 2025/06/23 23:20:32 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <stdlib.h>

int ft_strlen(char *str)
{
	int i;
	
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

unsigned long long ft_atoi(int len, char *nbr)
{
	unsigned long long nombre;
	int i;

	i = 0;
	nombre = 0;
	while (nbr[i] != '\0')
	{
		nombre = nombre + nbr[i] - '0';
		if (len > i)
			nombre *= 10;
		i++;
	}
	return nombre;
}
#include <stdio.h>

int check_number(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while(str[i] != '\0')
		{
			
			if(!(str[i] >= '0' && str[i] <= '9'))
			{
				return -1;

			}
			i++;
		}
		return 0;
	}
	else
	{
		while(str[i] != '\0')
		{
			if(!(str[i] >= '0' && str[i] <= '9'))
				return -1;
			i++;
		}
		return 0;
	}
}

int ft_modulo_number(unsigned long long number)
{
	int i;
	int g;
	
	i = number / 256;
	g = i * 256;
	
	return (number - g);
}

void ft_exit (int len, int argc, char **str)
{
	if (argc == 2)
	{
		if (ft_strcmp(str[1], "exit") == 0)
		{
			exit(0);
		}		
	}
	else
	if (argc > 2)
	{
		if (ft_strcmp(str[1], "exit") == 0)
		{
			if (check_number(str[2]) == 0 && argc == 3 && len <= 18)
			{
				exit(ft_modulo_number(ft_atoi((len), str[2])));
			}
			else if (check_number(str[2]) == 0 && argc > 3 && len <= 18)
			{
				ft_put_string("exit: too many arguments\n");
				exit(1);
			}
			else
			{
				ft_put_string("exit: ");
				ft_put_string(str[2]);
				ft_put_string(": numeric argument required\n");
				exit(255);
			}
		}	
	}

}

int main(int argc, char **argv)
{
	unsigned long long t;
	int len;
	len = 0;
	if (argc > 2)
		len = ft_strlen(argv[2]) - 1;
	//t = ft_atoi(len, argv[1]);
	//printf("%llu\n", t);
	//exit(0);


	//printf("%d", check_number(argv[1]));
	//printf("%d\n", ft_modulo_number(9223372036854775807));
	
	ft_exit (len, argc, argv);
}
