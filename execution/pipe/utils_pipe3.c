/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:54:21 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/16 03:54:38 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_status(t_exec *data, int *status)
{
	if (WIFEXITED(*status))
	{
		if (g_handl_signals == 2 && !data->cmd[0])
			;
		else
			ft_exit_status(WEXITSTATUS(*status), 1);
	}
	else if (WIFSIGNALED(*status))
		ft_check_signals(&(*status));
}
