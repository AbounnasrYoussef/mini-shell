/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 05:54:12 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/20 12:39:13 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

#include <fcntl.h>

int main(int argc, char **argv, char **env)
{
	char *cmd;
	int fd2;
	int fd[2];
	int c;
	
	fd[0] = 0;
	fd[1] = 1;
	
	int id;
	cmd = NULL;
	if (argv[1] != NULL)
	{
		cmd = cherche_path_cmd(argv[1], env);
	}

	id = fork();
	char *argvv[2];
	argvv[0] = argv[1];
	argvv[1] = NULL;
	if (id == 0)
	{
		if (ft_strcmp(argv[2], "<") == 0)
		{
			fd2 = open(argv[3], O_RDONLY);
			dup2(fd2, STDIN_FILENO);
			close(fd2);
		}
		else if (ft_strcmp(argv[2], ">") == 0)
		{
			fd2 = open(argv[3], O_CREAT | O_RDWR | O_TRUNC,0777);
			dup2(fd2, STDOUT_FILENO);
			close(fd2);
		}
		else if (ft_strcmp(argv[2], ">>") == 0)
		{
			fd2 = open(argv[3], O_CREAT | O_RDWR | O_APPEND, 0777);
			dup2(fd2, STDOUT_FILENO);
			close(fd2);
		}
		execve(cmd, argvv, NULL);
		
	}
	if (id != 0)
	{
		waitpid(id, NULL, 0);
	}
}


