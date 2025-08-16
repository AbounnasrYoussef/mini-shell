/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/16 16:05:26 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/execution.h"

int	g_handl_signals = 0;

void	env_i_and_readline(char **envp, t_read_loop *inf_read, int flag)
{
	char **str;
	
	str = ft_malloc(&(*inf_read).garb, 6 * sizeof(char *));
	if (flag == 0)
	{
		str[0] = PATHD;
		str[1] = ft_concat("PWD=", getcwd(NULL, 0), &(*inf_read).garb);
		str[2] = "SHLVL = 1";
		str[3] = "_=/usr/bin/env";
		str[4] = "OLDPWD";
		str[5] = NULL;
		if (envp[0] == NULL)
			(*inf_read).env = ft_envvv(str, &(*inf_read).garb);
		else
			(*inf_read).env = ft_envvv(envp, &((*inf_read).garb));
	}
	else if (flag == 1)
	{
		g_handl_signals = 0;
		save_terminal_settings();
		setup_signals();
		(*inf_read).garb = NULL;
		(*inf_read).line = readline("minishell$ ");
	}
}

void	ft_herdoc_piepe(t_exec **data, t_read_loop *inf_read)
{
	if ((*data)->files != NULL)
	{
		process_heredocs((*inf_read).line, *data,
			(*inf_read).env, &(*inf_read).garb);
		if (g_handl_signals != 3)
			ft_exit_status(0, 1);
	}
	if (*data != NULL && g_handl_signals != 3)
	{
		ft_pipe(*data, &(*inf_read).env, &(*inf_read).garb);
		*data = NULL;
	}
}

int	ft_parsing(t_exec **data, t_read_loop inf_read, int flag)
{
	if (flag == 0)
	{
		if (syntaxe_errors((inf_read).line) == 0)
		{
			(free((inf_read).line), free_exec_list(*data));
			return (0);
		}
	}
	else if (flag == 1)
	{
		if (!inf_read.token)
		{
			free(inf_read.line);
			return (0);
		}
	}
	else if (flag == 2)
	{
		if (!*data)
		{
			ft_free_all(inf_read.garb);
			return (0);
		}
	}
	return (1);
}

void	ft_read_loop(char **envp, t_exec **data)
{
	t_read_loop	inf_read;

	env_i_and_readline(envp, &inf_read, 0);
	while (1)
	{
		env_i_and_readline(envp, &inf_read, 1);
		if (!inf_read.line)
			break ;
		if (*inf_read.line)
			add_history(inf_read.line);
		if (ft_parsing(data, inf_read, 0) == 0)
			continue ;
		inf_read.token = tokens(inf_read.line, &inf_read.garb, &inf_read.ctx);
		if (ft_parsing(data, inf_read, 1) == 0)
			continue ;
		expand_all_tokens(&inf_read.token, inf_read.last_exit_code,
			inf_read.env, inf_read.ctx);
		*data = parse_tokens_to_exec_list(inf_read.token, &inf_read.garb);
		if (ft_parsing(data, inf_read, 2) == 0)
			continue ;
		ft_herdoc_piepe(data, &inf_read);
	}
	ft_free_all(inf_read.garb);
}

int	main(int ac, char **av, char **envp)
{
	t_exec		*data;

	(void)ac;
	(void)av;
	data = NULL;
	if (!isatty(0) || !isatty(1))
		return (1);
	ft_read_loop(envp, &data);
	return (0);
}
