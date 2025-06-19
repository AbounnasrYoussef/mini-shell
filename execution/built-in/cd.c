/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:24:19 by arahhab           #+#    #+#             */
/*   Updated: 2025/06/19 23:46:17 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int main(int ac, char **av)
{
	while (1)
	{
		char *line = readline("minishell: ");
		int a = chdir(line);
		printf("%d %s\n", a, getcwd(NULL, 0));
	}
	
	return 0;
}