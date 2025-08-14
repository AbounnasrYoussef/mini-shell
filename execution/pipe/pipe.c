/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:36:08 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/14 10:50:53 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../minishell.h"

void	ft_one_cmd(t_exec *data, t_list_env **env, int count_cmd
		, t_garbage **garb)
{
	int	original_fd_in;
	int	original_fd_out;

	if (data->files == NULL)
		ft_built_in(data, env, count_cmd, garb);
	else
	{
		original_fd_in = dup(STDIN_FILENO);
		original_fd_out = dup(STDOUT_FILENO);
		ft_redirection(data, garb);
		ft_built_in(data, env, count_cmd, garb);
		dup2(original_fd_in, STDIN_FILENO);
		dup2(original_fd_out, STDOUT_FILENO);
		close(original_fd_in);
		close(original_fd_out);
	}
}

void	ft_exec_child(t_exec *data, t_list_env **env, t_info_pipe inf_pip
		, t_garbage **garb)
{
	if (data->files != NULL)
		ft_redirection(data, garb);
	stat(data->cmd[0], &(inf_pip.info));
	ft_error_pipe(data, garb);
	ft_error_pipe2(data, inf_pip, garb);
	inf_pip.in_bultin = ft_built_in(data, env, inf_pip.count_cmd, garb);
	if (inf_pip.in_bultin == -1)
	{
		inf_pip.path_cmd = cherch_path(env, data, inf_pip.count_cmd, garb);
		if (inf_pip.path_cmd)
		{
			data->cmd[0] = inf_pip.path_cmd;
			execve(inf_pip.path_cmd, data->cmd, inf_pip.tab_envv);
			(ft_free_all(*garb), exit(0));
		}
		if (access(data->cmd[0], X_OK) == -1)
			norm_ft_exec_child(data->cmd[0], garb);
	}
	else
		(ft_free_all(*garb), exit(ft_exit_status(0, 0)));
}

# include <termios.h>

struct termios	*ft_get_termios(void)
{
	static struct termios	saved_termios;

	return (&saved_termios);
}

void	save_terminal_settings(void)
{
	tcgetattr(STDIN_FILENO, ft_get_termios());
}

void	restore_terminal_settings(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, ft_get_termios());
}


void	ft_child(t_exec *data, t_list_env **env, t_info_pipe *inf_pip
		, t_garbage **garb)
{
	
	if (inf_pip->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (inf_pip->in_fd != STDIN_FILENO)
		{
			dup2(inf_pip->in_fd, STDIN_FILENO);
			close(inf_pip->in_fd);
		}
		if (data->next != NULL)
		{
			dup2(inf_pip->fd[1], STDOUT_FILENO);
			1 && (close(inf_pip->fd[0]), close(inf_pip->fd[1]));
		}
		ft_exec_child(data, env, *inf_pip, garb);
	}
	else
	{
		if (data->next != NULL)
			close(inf_pip->fd[1]);
		if (inf_pip->in_fd != STDIN_FILENO)
			close(inf_pip->in_fd);
		if (data->next != NULL)
			inf_pip->in_fd = inf_pip->fd[0];
	}
}

void	ft_plusieur_cmd(t_exec *data, t_list_env **env, t_info_pipe *inf_pip
		, t_garbage **garb)
{
	signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
	while (data != NULL)
	{
		if (data->next != NULL)
		{
			if (pipe(inf_pip->fd) == -1)
			{
				perror("pipe");
				ft_free_all(*garb);
				exit(1);
			}
		}
		inf_pip->pid = fork();
		if (inf_pip->pid == -1)
		{
			ft_exit_status(1, 1);
			return (ft_error_fork());
		}
		else
		{
			ft_child(data, env, inf_pip, garb);
		}
		data = data->next;
		(inf_pip->i)++;
	}
}

void	ft_pipe(t_exec *data, t_list_env **env, t_garbage **garb)
{
	t_info_pipe	inf_pip;
	int			status;

	inf_pip.i = 0;
	inf_pip.j = 0;
	inf_pip.in_fd = STDIN_FILENO;
	inf_pip.tab_envv = tab_env(*env, garb);
	inf_pip.count_cmd = count_cmd(data);
	if (count_cmd(data) == 1 && ft_strlen_argc(data->cmd) == 1
		&& ft_strcmpp(data->cmd[0], "export") != 0
		&& is_built_in(data->cmd[0]) == 0)
		return (ft_one_cmd(data, env, count_cmd(data), garb));
	else if (count_cmd(data) == 1 && ft_strlen_argc(data->cmd) != 1
		&& is_built_in(data->cmd[0]) == 0)
		return (ft_one_cmd(data, env, count_cmd(data), garb));
	else
		ft_plusieur_cmd(data, env, &inf_pip, garb);
	waitpid(inf_pip.pid, &status, 0);
	if (WIFEXITED(status))
		ft_exit_status(WEXITSTATUS(status), 1);
	else if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == SIGQUIT)
            write(STDOUT_FILENO, "Quit: 3\n", 8);
        else if (WTERMSIG(status) == SIGINT)
            write(STDOUT_FILENO, "\n", 1);
        ft_exit_status(WTERMSIG(status) + 128, 1);
    }
	ft_wait_child(&inf_pip);
	restore_terminal_settings();
	setup_signals();
}
