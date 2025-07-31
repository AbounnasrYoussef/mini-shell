/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:44:05 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 18:15:18 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_exec_list(t_exec *exec_list)
{
	t_exec	*tmp;
	int		i;

	while (exec_list)
	{
		tmp = exec_list->next;
		if (exec_list->cmd)
		{
			i = 0;
			while (exec_list->cmd[i])
			{
				free(exec_list->cmd[i]);
				i++;
			}
			free(exec_list->cmd);
		}
		free(exec_list);
		exec_list = tmp;
	}
}
