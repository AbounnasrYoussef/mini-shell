/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:21:08 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/14 06:15:29 by arahhab          ###   ########.fr       */
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

int count_nbr_herdoc(t_file *file)
{
	int i;

	i = 0;
	while (file != NULL)
	{
		if (file->type == HERE_DOC)
			i++;
		file = file->next;
	}
	return (i);
}
void	process_heredocs(char *line, t_exec *exec)
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
				if (count_nbr_herdoc(file) > 15)
				{
					printf("maximum here-document count exceeded\n");
					exit(2);
				}
				file->fd = create_heredoc(file->file_name);
				
			}
			file = file->next;
		}
		exec = exec->next;
	}
}
