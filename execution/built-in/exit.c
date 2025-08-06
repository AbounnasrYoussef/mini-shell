/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:45:34 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/06 23:50:16 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	error_exit(char *str, int count_cmd, t_garbage **garb)
{
	if (count_cmd == 1)
		write(2, "exit: ", 6);
	write(2, str, ft_strlenn(str));
	write(2, ": numeric argument required\n", 28);
	ft_free_all(*garb);
	exit(255);
}

unsigned long long	ft_atoi(int len, char *nbr, int count_cmd, t_garbage **garb)
{
	unsigned long long	nombre;
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	nombre = 0;
	if (nbr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (nbr[i] != '\0')
	{
		nombre = nombre + nbr[i] - '0';
		if ((sign == -1) && (nombre > (9223372036854775807)) && nbr[19] > '8')
			error_exit(nbr, count_cmd, garb);
		else if (nombre > (9223372036854775807))
			error_exit(nbr, count_cmd, garb);
		if (len > i)
			nombre *= 10;
		i++;
	}
	return (nombre);
}

int	check_number(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-')
	{
		i++;
		while (str[i] != '\0')
		{
			if (!(str[i] >= '0' && str[i] <= '9'))
				return (-1);
			i++;
		}
		return (0);
	}
	else
	{
		while (str && str[i] != '\0')
		{
			if (!(str[i] >= '0' && str[i] <= '9'))
				return (-1);
			i++;
		}
		return (0);
	}
}

int	modulo(unsigned long long number)
{
	int	i;
	int	g;

	i = number / 256;
	g = i * 256;
	return (number - g);
}

void	error_exit2(int count_cmd, int *status)
{
	if (count_cmd == 1)
		printf("exit\n");
	write(2, "exit: too many arguments\n", 25);
	*status = 1;
}

void	ft_exit (t_exit i_exi, char **str, t_garbage **garb, int *status)
{
	i_exi.argc = ft_strlen_argc(str);
	if (i_exi.argc >= 1)
	{
		if (ft_strcmpp(str[0], "exit") == 0)
		{
			if (str[1] == NULL)
			{
				if (i_exi.c_cmd == 1)
					printf("exit\n");
				exit(ft_exit_status(0, 0));	
			}
			else if (ft_strcmpp(str[1], "") == 0)
			{
				error_exit(str[1], i_exi.c_cmd, garb);
			}
			else if (check_number(str[1]) == 0 && i_exi.argc == 2 && i_exi.len <= 19)
			{
				if (i_exi.c_cmd == 1)
					printf("exit\n");
				exit(modulo(ft_atoi((i_exi.len), str[1], i_exi.c_cmd, garb)));
			}
			else if (check_number(str[1]) == 0 && i_exi.argc > 2 && i_exi.len <= 19)
				error_exit2(i_exi.c_cmd, status);
			else
				error_exit(str[1], i_exi.c_cmd, garb);
		}
	}
}
