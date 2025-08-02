/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:10:23 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/02 18:03:38 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_redirection(t_exec *data)
{
	t_file *file;
	int fd;
	int fd_herdoc;
	struct stat info;
	
	fd_herdoc = -1;
	file = data->files;
	while(file != NULL)
	{
		stat(file->file_name, &info);
		if (file->type == 2)
		{
			fd = open(file->file_name, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (file->type == 3)
		{
			fd = open(file->file_name, O_CREAT | O_RDWR | O_TRUNC,0777);
			if(fd == -1 && S_ISDIR(info.st_mode))
			{
				write(2, file->file_name, ft_strlenn(file->file_name));
				(write(2, ": is a directory \n", 18), exit(1));
			}
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
		if (fd == -1 && !S_ISDIR(info.st_mode) && !S_ISREG(info.st_mode))
		{
			write(2, file->file_name, ft_strlenn(file->file_name));
			write(2, ": No such file or directory\n", 28);
			exit(1);
		}
		else if(fd == -1 && access(file->file_name, X_OK) == -1)
		{
			perror("access");
		}
		if (file->fd == -1)
		{
			perror("dup2");
		}
		file = file->next;
	}
}