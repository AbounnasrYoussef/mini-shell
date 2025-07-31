/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:10:23 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/31 22:23:01 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_redirection(t_exec *data)
{
	t_file *file;
	int fd;
	int fd_herdoc;
	
	fd_herdoc = -1;
	file = data->files;
	while(file != NULL)
	{
		if (file->type == 2)
		{
			fd = open(file->file_name, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (file->type == 3)
		{
			fd = open(file->file_name, O_CREAT | O_RDWR | O_TRUNC,0777);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (file->type == 4)
		{
			fd = open(file->file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (file->type == 5)
		{
			dup2(file->fd, STDIN_FILENO);
			close(file->fd);
		}
		file = file->next;
	}
}