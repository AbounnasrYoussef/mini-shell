/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:53:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/14 06:42:39 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_exit_status(130 , 1);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	//signal(SIGQUIT, handle_sigquit);
	signal(SIGQUIT, SIG_IGN);

}
