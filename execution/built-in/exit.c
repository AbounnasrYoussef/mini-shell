/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:45:34 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/29 21:03:10 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void msg_err_atoi(char *nbr)
{
	printf("exit\n");
	write(2, nbr, ft_strlenn(nbr));
	write(2, ": numeric argument required\n", 28);
	exit(255);
}

unsigned long long ft_atoi(int len, char *nbr)
{
	unsigned long long nombre;
	int i;
	int sign;

	i = 0;
	sign = 1;
	nombre = 0;
	if (nbr[i] == '-')
		(sign = -1, i++);
	while (nbr[i] != '\0')
	{
		nombre = nombre + nbr[i] - '0';
		if ((sign == -1) && (nombre > (9223372036854775807)))
		{
			if (nbr[19] > '8')
				msg_err_atoi(nbr);
		}
		else if (nombre > (9223372036854775807))
			msg_err_atoi(nbr);	
		if (len > i)
			nombre *= 10;
		i++;
	}
	return nombre;
}

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
				return -1;
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

void error_exit(char **str)
{
	printf("exit\n");
	write(2, str[1], ft_strlenn(str[1]));
	write(2, ": numeric argument required\n", 28);
	exit(255);
}

void ft_exit (int len, char **str)
{
	int argc;
	
	argc = ft_strlen_argc(str);
	if (argc >= 1)
	{
		if (ft_strcmpp(str[0], "exit") == 0)
		{
			if (str[1] == NULL)
				(write(2, "exit\n", 5), exit(0));
			else if (check_number(str[1]) == 0 && argc == 2 && len <= 19)
			{
				write(2, "exit\n", 5);
				exit(ft_modulo_number(ft_atoi((len), str[1])));
			}
			else if (check_number(str[1]) == 0 && argc > 2 && len <= 19)
				write(2, "exit: too many arguments\n", 25);
			else
				error_exit(str);
		}
	}
}
