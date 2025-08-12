/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:29:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/12 16:41:22 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	write_heredoc_line(char *line, int expand, t_list_env *env,
		t_garbage **garb, int fd)
{
	char	*final;

	if (expand)
	{
		if (heredoc_expansion(line, env, garb, &final) == -1)
			return (-1);
	}
	else
		final = ft_strdup(line, garb);
	write(fd, final, ft_strlen(final));
	write(fd, "\n", 1);
	return (0);
}

int	create_heredoc(char *delimiter, int expand, t_list_env *env,
		t_garbage **garb)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		if (write_heredoc_line(line, expand, env, garb, fd[1]) == -1)
			return (free(line), close(fd[0]), close(fd[1]), -1);
		free(line);
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}

