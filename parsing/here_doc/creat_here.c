/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:29:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/14 06:28:15 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//static int	write_heredoc_line(char *line, t_heredoc_ctx *ctx)
//{
//	char	*final;

//	if (ctx->expand)
//	{
//		if (heredoc_expansion(line, ctx->env, ctx->garb, &final) == -1)
//			return (-1);
//	}
//	else
//		final = ft_strdup(line, ctx->garb);
//	write(ctx->fd, final, ft_strlen(final));
//	write(ctx->fd, "\n", 1);
//	return (0);
//}

//int	create_heredoc(char *delimiter, int expand, t_list_env *env,
//		t_garbage **garb)
//{
//	int				fd[2];
//	char			*line;
//	t_heredoc_ctx	ctx;
//	int				i;

//	i = 0;
//	if (pipe(fd) == -1)
//		return (perror("pipe"), -1);
//	ctx.expand = expand;
//	ctx.env = env;
//	ctx.garb = garb;
//	ctx.fd = fd[1];
//	g_handl_signals = 3;
//	while (1)
//	{
//		if (g_handl_signals == 4)
//			break ;
//		line = readline("> ");
//		i++;
//		if (!line || ft_strcmp(line, delimiter) == 0)
//			break ;
//		if (write_heredoc_line(line, &ctx) == -1)
//			return (free(line), close(fd[0]), close(fd[1]), -1);
//		free(line);
//	}
//	if (g_handl_signals == 4)
//		return (ft_exit_status(1, 1));
//	free(line);
//	close(fd[1]);
//	return (fd[0]);
//}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

int	create_heredoc(char *delimiter)
{
	int				fd[2];
	pid_t			pid;
	int				status;
	
	void			(*original_sigint_handler)(int);

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);

	original_sigint_handler = signal(SIGINT, SIG_IGN);

	pid = fork();
	if (pid == -1)
	{
		signal(SIGINT, original_sigint_handler);
		return (perror("fork"), -1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);

		close(fd[0]);
		char *line;
		while (1)
		{
			line = readline("> ");
			if (!line)
				break;
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break;
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		exit(0);
	}
	else
	{
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
		else
		{
			close(fd[0]);
			return (-1);
		}
	}
}