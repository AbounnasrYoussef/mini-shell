/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:45:34 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/29 14:21:07 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../execution.h"

//unsigned long long ft_atoi(int len, char *nbr)
//{
//	unsigned long long nombre;
//	int i;

//	i = 0;
//	nombre = 0;
//	while (nbr[i] != '\0')
//	{
//		nombre = nombre + nbr[i] - '0';
//		if (len > i)
//			nombre *= 10;
//		i++;
//	}
//	return nombre;
//}

//int check_number(char *str)
//{
//	int i;

//	i = 0;
//	if (str[i] == '-')
//	{
//		i++;
//		while(str[i] != '\0')
//		{
			
//			if(!(str[i] >= '0' && str[i] <= '9'))
//			{
//				return -1;

//			}
//			i++;
//		}
//		return 0;
//	}
//	else
//	{
//		while(str[i] != '\0')
//		{
//			if(!(str[i] >= '0' && str[i] <= '9'))
//				return -1;
//			i++;
//		}
//		return 0;
//	}
//}

//int ft_modulo_number(unsigned long long number)
//{
//	int i;
//	int g;
	
//	i = number / 256;
//	g = i * 256;
	
//	return (number - g);
//}

//void ft_exit (int len, int argc, char **str)
//{
//	if (argc == 1)
//	{
//		if (ft_strcmpp(str[0], "exit") == 0)
//		{
//			printf("shhs\n");
//			exit(0);
//		}		
//	}
//	else if (argc > 1)
//	{
//		if (ft_strcmpp(str[0], "exit") == 0)
//		{
//			if (check_number(str[1]) == 0 && argc == 2 && len <= 18)
//			{
//				exit(ft_modulo_number(ft_atoi((len), str[1])));
//			}
//			else if (check_number(str[1]) == 0 && argc > 2 && len <= 18)
//			{
//				ft_put_string("exit: too many arguments\n");
//				//exit(1);
//			}
//			else
//			{
//				ft_put_string("exit: ");
//				ft_put_string(str[1]);
//				ft_put_string(": numeric argument required\n");
//				exit(255);
//			}
//		}	
//	}

//}


#include "../execution.h"


unsigned long long ft_atoi(int len, char *nbr)
{
	unsigned long long nombre;
	int i;
	int sign;

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
		
		if (sign == -1)
		{
			if (nombre > (9223372036854775807))
			{
				if (nbr[19] > '8')
				{
					printf("exit\n");
					printf("%s : numeric argument required\n", nbr);
					exit(255);
				}
			}
		}
		else
		{
			if (nombre > (9223372036854775807))
			{
				printf("exit\n");
				printf("%s : numeric argument required\n", nbr);
				
				exit(255);
			}
		}
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

void ft_exit (int len, char **str)
{
	int argc;
	
	argc = ft_strlen_argc(str);
	if (argc >= 1)
	{
		if (ft_strcmpp(str[0], "exit") == 0)
		{
			
			if (str[1] == NULL)
			{
				write(2, "exit\n", 5);
				exit(0);
			}
			else if (check_number(str[1]) == 0 && argc == 2 && len <= 19)
			{
				write(2, "exit\n", 5);
				exit(ft_modulo_number(ft_atoi((len), str[1])));
			}
			else if (check_number(str[1]) == 0 && argc > 2 && len <= 19)
			{
				write(2, "exit: too many arguments\n", 25);
			}
			else
			{
				write(2, "exit\n", 5);
				write(2, "exit", 4);
				write(2, str[1], ft_strlenn(str[1]));
				write(2, ": numeric argument required\n", 28);
				exit(255);
			}
		}
	}

}
