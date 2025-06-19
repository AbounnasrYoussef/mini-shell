/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:49:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/06/19 23:57:20 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

#define buffer_size 1000


void ft_pwd(void)
{
	char buffer[buffer_size];
	getcwd(buffer, buffer_size);
	//printf("\n\n\n\n %s \n\n\n\n\n", buffer);
	ft_put_string(buffer);
}

int main()
{
	ft_pwd();
}