/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:21:08 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 17:54:51 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int heredoc_expand(char *line, t_list_env *env, t_garbage **garb, char **res)
{
	int i = 0;
	char *tmp = ft_strdup("", garb);
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '?')
			{
				char *status = ft_itoa(g_exit_status, garb);
				tmp = ft_strjoin(tmp, status, garb);
				i++;
			}
			else if (ft_isalpha(line[i]) || line[i] == '_')
			{
				int start = i;
				while (ft_isalnum(line[i]) || line[i] == '_')
					i++;
				char *name = ft_substr(line, start, i - start, garb);
				char *val = get_env_value(name, env, garb);
				tmp = ft_strjoin(tmp, val, garb);
			}
			else
			{
				char raw[3] = {'$', line[i], 0};
				tmp = ft_strjoin(tmp, raw, garb);
				i++;
			}
		}
		else
		{
			char c[2] = {line[i++], 0};
			tmp = ft_strjoin(tmp, c, garb);
		}
	}
	*res = tmp;
	return (0);
}

static int create_heredoc(char *delimiter, int expand, t_list_env *env, t_garbage **garb)
{
	char	*line;
	char	*final;
	int		fd[2];
	pipe(fd);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break;
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
	while (exec)
	{
		t_file *file = exec->files;
		while (file)
		{
			if (file->type == HERE_DOC)
			{
				int	expand = 1;
				if (file->file_name[0] == '\'' || file->file_name[0] == '"')
					expand = 0;

				file->fd = create_heredoc(file->file_name, expand, env, garb);

				//char	*fd_str = ft_itoa(fd, garb); // convertit le fd en chaîne
				//char	*fd_path = ft_strjoin("", fd_str, garb); // crée le chemin final
				//file->file_name = fd_path;
			}
			file = file->next;
		}
		exec = exec->next;
	}
}
