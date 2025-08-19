/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:36:44 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/19 15:00:40 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/execution.h"

void	norm_read_loop(t_exec **data, t_read_loop	inf_read)
{
	expand_all_tokens(&inf_read.token, inf_read.last_exit_code,
		inf_read.env, inf_read.ctx);
	*data = parse_tokens_to_exec_list(inf_read.token, &inf_read.garb);
}
