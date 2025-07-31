/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:36:08 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/31 22:19:56 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include "../../minishell.h"

void ft_pipe(int argc, t_exec *data, t_list_env *env)
{
    int i;
    int pid;
    int fd[2];
    int in_fd; 
	char *path_cmd;
	int in_bultin;
	struct stat info;
	int j;
	int original_fd_in;
	int original_fd_out;
	char **tab_envv;
	
	j = 0;
	in_fd = STDIN_FILENO;
	i = 0;
	in_bultin = 0;
	tab_envv = tab_env(env);
	if(count_cmd(data) == 1 && ft_strlen_argc(data->cmd) == 1 
		&& ft_strcmpp(data->cmd[0], "export") != 0 && is_built_in(data->cmd[0]) == 0)
	{
		if (data->files == NULL)
			ft_built_in(argc, data, env);
		else
		{
			original_fd_in = dup(STDIN_FILENO);
			original_fd_out = dup(STDOUT_FILENO);
			ft_redirection(data);
			ft_built_in(argc, data, env);
			dup2(original_fd_in, STDIN_FILENO);
			dup2(original_fd_out, STDOUT_FILENO);
			close(original_fd_in);
			close(original_fd_out);
		}
	}
	else if (count_cmd(data) == 1 && ft_strlen_argc(data->cmd) != 1 && is_built_in(data->cmd[0]) == 0)
	{
		if (data->files == NULL)
			ft_built_in(argc, data, env);
		else
		{
			original_fd_in = dup(STDIN_FILENO);
			original_fd_out = dup(STDOUT_FILENO);
			ft_redirection(data);
			ft_built_in(argc, data, env);
			dup2(original_fd_in, STDIN_FILENO);
			dup2(original_fd_out, STDOUT_FILENO);
			close(original_fd_in);
			close(original_fd_out);
		}
	}
	else
	{
		while (data != NULL)
		{
			if (data->next != NULL)
			{
				if (pipe(fd) == -1)
				{
					perror("pipe");
					exit(1);
				}
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(1);
			}
			else if (pid == 0)
			{
				if (in_fd != STDIN_FILENO)
				{
					dup2(in_fd, STDIN_FILENO);
					close(in_fd);
				}
				if (data->next != NULL)
				{
					dup2(fd[1], STDOUT_FILENO);
					close(fd[0]);
					close(fd[1]);
				}
				if (data->files != NULL)
					ft_redirection(data);
				stat(data->cmd[0], &info);
				if (S_ISDIR(info.st_mode))
				{
					if ((data->cmd[0][0] == '.' && data->cmd[0][1] == '/') || data->cmd[0][0] == '/')
					{
						write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
						write(2, ": is a directory \n", 18);
						exit(1);
					}	
				}
				else if (!S_ISREG(info.st_mode) && is_slash(data->cmd[0]) == 0)
				{
					write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
					write(2, ": No such file or directory\n", 28);
					exit(1);
				}
				in_bultin = ft_built_in(argc, data, env);
				if (in_bultin == -1)
				{
					path_cmd = cherche_path_cmd(data->cmd[0], env, argc, data);
					if (path_cmd)
					{
						execve(path_cmd, data->cmd, tab_envv); 
						exit(1);
					}
				}
				else
				{
					exit(1);
				}
			}
			else
			{
				if (data->next != NULL)
				{
					close(fd[1]);
				}
				if (in_fd != STDIN_FILENO)
				{
					close(in_fd);
				}
				if (data->next != NULL)
				{
					in_fd = fd[0];
				}
			}
			data = data->next;
			i++;
		}		
	}
    int status;
    while(j < i)
    {
        wait(&status);
		j++;
    }
}
