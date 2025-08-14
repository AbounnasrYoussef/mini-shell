/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:29:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/14 21:15:52 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

// int	create_heredoc(char *delimiter)
// {
// 	int				fd[2];
// 	pid_t			pid;
// 	int				status;
// 	void			(*original_sigint_handler)(int);

// 	if (pipe(fd) == -1)
// 		return (perror("pipe"), -1);

// 	original_sigint_handler = signal(SIGINT, SIG_IGN);

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		signal(SIGINT, original_sigint_handler);
// 		return (perror("fork"), -1);
// 	}
// 	else if (pid == 0)
// 	{
// 		signal(SIGINT, handle_sigint_heredoc);

// 		close(fd[0]);
// 		char *line;
// 		while (1)
// 		{
// 			line = readline("> ");
// 			if (!line)
// 				break;
// 			if (ft_strcmp(line, delimiter) == 0)
// 			{
// 				free(line);
// 				break;
// 			}
// 			write(fd[1], line, ft_strlen(line));
// 			write(fd[1], "\n", 1);
// 			free(line);
// 		}
// 		close(fd[1]);
// 		exit(0);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		waitpid(pid, &status, 0);
// 		signal(SIGINT, original_sigint_handler);
// 		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
// 		{
// 			ft_exit_status(1, 1);
// 			close(fd[0]);
// 			return (-1);
// 		}
// 		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
// 			return (fd[0]);
// 		else
// 		{
// 			close(fd[0]);
// 			return (-1);
// 		}
// 	}
// }

static void	run_heredoc_child(int *fd, char *delimiter)
{
	char	*line;

	signal(SIGINT, handle_sigint_heredoc);
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	exit(0);
}

static int	handle_parent_heredoc(int *fd, pid_t pid,
		void (*original_sigint_handler)(int))
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, original_sigint_handler);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		ft_exit_status(1, 1);
		close(fd[0]);
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (fd[0]);
	close(fd[0]);
	return (-1);
}

int	create_heredoc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;
	void	(*original_sigint_handler)(int);

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	original_sigint_handler = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		signal(SIGINT, original_sigint_handler);
		return (perror("fork"), -1);
	}
	if (pid == 0)
		run_heredoc_child(fd, delimiter);
	return (handle_parent_heredoc(fd, pid, original_sigint_handler));
}
