/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utili_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:19:37 by arahhab           #+#    #+#             */
/*   Updated: 2025/06/22 15:49:39 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void ft_put_string(char *str)
{
	int i;
	
	i = 0;
	if(str == NULL)
	{
		write(1, " ", 1);
		return ;
	}
	while(str[i] != '\0')
	{
		write(1,&str[i], 1);
		i++;
	}
	return ;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}