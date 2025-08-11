/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:29:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/10 13:31:50 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	write_heredoc_line(int fd, char *line, int expand,
		t_list_env *env, t_garbage **garb)
{
	char	*final;

	if (expand)
	{
		if (heredoc_expansion(line, env, garb, &final) == -1)
			return (-1);
	}
	else
		final = ft_strdup(line, garb);
	if (!final)
		return (-1);
	write(fd, final, ft_strlen(final));
	write(fd, "\n", 1);
	return (0);
}

int	create_heredoc(char *delimiter, int expand,
		t_list_env *env, t_garbage **garb)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
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
		if (write_heredoc_line(fd[1], line, expand, env, garb) == -1)
		{
			free(line);
			close(fd[0]);
			close(fd[1]);
			return (-1);
		}
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}
