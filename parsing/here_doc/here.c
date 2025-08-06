/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:21:08 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/06 15:39:55 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	heredoc_expand(char *line, t_list_env *env, t_garbage **garb, char **res)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("", garb);
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '?')
				i += append_exit_status(&tmp, garb);
			else if (ft_isalpha(line[i]) || line[i] == '_')
				i = append_variable(line + i, env, garb, &tmp);
			else
				append_raw_dollar(&tmp, line[i++], garb);
		}
		else
			append_normal_char(&tmp, line[i++], garb);
	}
	*res = tmp;
	return (0);
}

int	create_heredoc(char *delimiter, int expand,
		t_list_env *env, t_garbage **garb)
{
	char	*line;
	char	*final;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		if (expand)
			heredoc_expand(line, env, garb, &final);
		else
			final = ft_strdup(line, garb);
		write(fd[1], final, ft_strlen(final));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	return (fd[0]);
}

void	process_heredocs(t_exec *exec, t_list_env *env, t_garbage **garb)
{
	t_file	*file;
	int		expand;

	while (exec)
	{
		file = exec->files;
		while (file)
		{
			if (file->type == HERE_DOC)
			{
				expand = 1;
				if (file->file_name[0] == '\'' || file->file_name[0] == '"')
					expand = 0;
				file->fd = create_heredoc(file->file_name, expand, env, garb);
			}
			file = file->next;
		}
		exec = exec->next;
	}
}
