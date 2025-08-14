/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:10:23 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/14 04:10:09 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	error_redr(int *fd, char *file_name, struct stat info)
{
	if (*fd == -1 && access(file_name, X_OK) == -1 && errno == 13)
	{
		perror("access");
		exit(1);
	}
	else if (*fd == -1 && !S_ISDIR(info.st_mode) && !S_ISREG(info.st_mode))
	{
		write(2, file_name, ft_strlenn(file_name));
		write(2, ": No such file or directory\n", 28);
		exit(1);
	}
}

void	error_dolar(char *file_name)
{
	write(2, file_name, ft_strlenn(file_name));
	write(2, ": ambiguous redirect\n", 21);
	exit(1);
	ft_exit_status(1, 1);
}

void	ft_redirection(t_exec *data, t_garbage **garb)
{
	t_file		*file;
	int			fd;
	struct stat	info;

	(void)garb;
	file = data->files;
	while (file != NULL)
	{
		stat(file->file_name, &info);
		//printf("'%s'", file->file_name);
		if (ft_strcmpp(file->file_name, "") == 0)
			error_dolar(file->file_name);
		if (file->type == 2)
			ft_input(&fd, file->file_name);
		else if (file->type == 3)
			ft_output(&fd, file->file_name, info);
		else if (file->type == 4)
			ft_output_append(&fd, file->file_name);
		else if (file->type == 5)
			ft_herdoc(&(file->fd));
		error_redr(&fd, file->file_name, info);	
		file = file->next;
	}
}
