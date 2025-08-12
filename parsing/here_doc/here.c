/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:21:08 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/12 16:45:50 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	append_char(char **tmp, char c, t_garbage **garb)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	*tmp = ft_strjoin(*tmp, str, garb);
}

// int	heredoc_expansion(char *line, t_list_env *env, t_garbage **garb, char **res)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	tmp = ft_strdup("", garb);
// 	while (line[i])
// 	{
// 		if (line[i] == '$')
// 		{
// 			i++;
// 			if (line[i] == '?')
// 			{
// 				char *exit_str = ft_itoa(ft_exit_status(0,0), garb);
// 				tmp = ft_strjoin(tmp, exit_str, garb);
// 				i++;
// 			}
// 			else if (is_valid_var_char(line[i]))
// 			{
// 				int start = i;
// 				while (is_valid_var_char(line[i]))
// 					i++;
// 				char *varname = ft_substr(line, start, i - start, garb);
// 				char *val = get_env_value(varname, env, garb);
// 				if (!val)
// 					val = ft_strdup("", garb);
// 				tmp = ft_strjoin(tmp, val, garb);
// 			}
// 			else
// 				append_char(&tmp, '$', garb);
// 		}
// 		else
// 			append_char(&tmp, line[i++], garb);
// 	}
// 	*res = tmp;
// 	return (0);
// }

// int create_heredoc(char *delimiter, int expand, t_list_env *env, t_garbage **garb)
// {
// 	int		fd[2];
// 	char	*line;
// 	char	*final;

// 	if (pipe(fd) == -1)
// 	{
// 		perror("pipe");
// 		return (-1);
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break;
// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		if (expand)
// 		{
// 			if (heredoc_expansion(line, env, garb, &final) == -1)
// 			{
// 				free(line);
// 				close(fd[0]);
// 				close(fd[1]);
// 				return (-1);
// 			}
// 		}
// 		else
// 			final = ft_strdup(line, garb);
// 		write(fd[1], final, ft_strlen(final));
// 		write(fd[1], "\n", 1);
// 		free(line);
// 	}
// 	close(fd[1]);
// 	return (fd[0]);
// }

void process_heredocs(char *line, t_exec *exec, t_list_env *env, t_garbage **garb)
{
	t_file	*file;
	int		expand = 1;

	while (exec)
	{
		file = exec->files;
		while (file)
		{
			if (ft_strchr(line,'\'') || ft_strchr(line,'"'))
			{
				expand = 0;
			}
			if (file->type == HERE_DOC)
			{
				file->fd = create_heredoc(file->file_name, expand, env, garb);
			}
			file = file->next;
		}
		exec = exec->next;
	}
}
