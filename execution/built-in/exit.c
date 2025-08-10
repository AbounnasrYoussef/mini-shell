/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:45:34 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/10 20:56:59 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_atoi(char *nbr, int count_cmd, t_garbage **garb)
{
	unsigned long long	nombre;
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	nombre = 0;
	while (nbr && (nbr[i] == ' ' || nbr[i] == '\t'))
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while (nbr[i] != '\0' && nbr[i] >= '0' && nbr[i] <= '9')
	{
		nombre = nombre + nbr[i] - '0';
		if ((sign == -1) && (nombre > (9223372036854775807)) && nbr[19] > '8')
			error_exit(nbr, count_cmd, garb);
		else if (nombre > (9223372036854775807))
			error_exit(nbr, count_cmd, garb);
		if (nbr[i + 1] >= '0' && nbr[i + 1] <= '9')
			nombre *= 10;
		i++;
	}
	return (modulo(nombre) * sign);
}

int	chck_nb(char *str)
{
	int	i;

	i = 0;
	while (str && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str && (str[i] == '-' || str[i] == '+'))
	{
		i++;
		while (str[i] != '\0')
		{
			if ((str[i] >= '0' && str[i] <= '9'))
			{
				while ((str[i] != '\0' && str[i] >= '0' && str[i] <= '9'))
					i++;
				while (str[i] == ' ' || str[i] == '\t')
					i++;
				if (ft_strcmpp(&str[i], "") == 0)
					return (0);
				else
					return (-1);
			}
			else
				return (-1);
			i++;
		}
		return (0);
	}
	else
	{
		while (str && str[i] != '\0')
		{
			if ((str[i] >= '0' && str[i] <= '9'))
			{
				while ((str[i] != '\0' && str[i] >= '0' && str[i] <= '9'))
					i++;
				while (str[i] == ' ' || str[i] == '\t')
					i++;
				if (ft_strcmpp(&str[i], "") == 0)
					return (0);
				else
					return (-1);
			}
			else
				return (-1);
			i++;
		}
		return (0);
	}
}

void	ft_exit(t_exit i_exi, char **str, t_garbage **garb)
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
				error_exit(str[1], i_exi.c_cmd, garb);
			else if (chck_nb(str[1]) == 0 && i_exi.argc == 2 && i_exi.len <= 19)
			{
				if (i_exi.c_cmd == 1)
					printf("exit\n");
				exit(ft_atoi(str[1], i_exi.c_cmd, garb));
			}
			else if (chck_nb(str[1]) == 0 && i_exi.argc > 2 && i_exi.len <= 19)
				error_exit2(i_exi.c_cmd);
			else
				error_exit(str[1], i_exi.c_cmd, garb);
		}
	}
}
