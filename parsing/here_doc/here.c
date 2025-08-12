/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:21:08 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/12 17:00:29 by yabounna         ###   ########.fr       */
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

void	process_heredocs(char *line, t_exec *exec,
		t_list_env *env, t_garbage **garb)
{
	t_file	*file;
	int		expand;

	expand = 1;
	while (exec)
	{
		file = exec->files;
		while (file)
		{
			if (ft_strchr(line, '\'') || ft_strchr(line, '"'))
				expand = 0;
			if (file->type == HERE_DOC)
			{
				file->fd = create_heredoc(file->file_name, expand, env, garb);
			}
			file = file->next;
		}
		exec = exec->next;
	}
}
