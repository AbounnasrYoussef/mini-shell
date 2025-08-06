/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:36:08 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/06 20:42:07 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../minishell.h"

typedef struct s_info_pipe
{
	int i;
    int pid;
    int fd[2];
    int in_fd; 
	char *path_cmd;
	int in_bultin;
	int j;
	char **tab_envv;
	struct stat info;
}t_info_pipe;

void ft_one_cmd(t_exec *data, t_list_env **env, int count_cmd, t_garbage **garb, int *status)
{
	int original_fd_in;
	int original_fd_out;
	
	if (data->files == NULL)
		ft_built_in(data, env, count_cmd, garb, status);
	else
	{
		original_fd_in = dup(STDIN_FILENO);
		original_fd_out = dup(STDOUT_FILENO);
		ft_redirection(data, garb);
		ft_built_in(data, env, count_cmd, garb, status);
		dup2(original_fd_in, STDIN_FILENO);
		dup2(original_fd_out, STDOUT_FILENO);
		close(original_fd_in);
		close(original_fd_out);
	}
}


void ft_exec_child(t_exec *data, t_list_env **env, t_info_pipe inf_pip, int count_cmd, t_garbage **garb, int *status)
{
	if ( data->files != NULL)
		ft_redirection(data, garb);
	stat(data->cmd[0], &(inf_pip.info));
	if (data->cmd[0] && data->cmd[0][0] == '.' && data->cmd[0][1] == '\0')
	{
		write(2, ".: filename argument required\n.: usage: . filename [arguments]\n", 63);
		ft_free_all(*garb);
		exit(2);
	}
	if (S_ISDIR((inf_pip.info).st_mode))
	{
		if ((data->cmd[0][0] == '.' && data->cmd[0][1] == '/') 
			|| data->cmd[0][0] == '/'
			|| (data->cmd[0][0] == '.' && data->cmd[0][1] == '.') )
		{
			write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
			write(2, ": is a directory \n", 18);
			ft_free_all(*garb);
			exit(126);
		}	
	}
	else if(!S_ISREG((inf_pip.info).st_mode) && ft_strlenn(data->cmd[0]) > 0 
			&& (data->cmd[0][ft_strlenn(data->cmd[0]) - 1] == '/'))
	{
		write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
		write(2, ": Not a directory\n", 18);
		ft_free_all(*garb);
		exit(126);
	}
	else if (!S_ISREG((inf_pip.info).st_mode) && is_slash(data->cmd[0]) == 0)
	{
		write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
		write(2, ": No such file or directory\n", 28);
		ft_free_all(*garb);
		exit(127);
	}
	inf_pip.in_bultin = ft_built_in(data, env, count_cmd, garb, status);
	if (inf_pip.in_bultin == -1)
	{
		inf_pip.path_cmd = cherche_path_cmd(data->cmd[0], env, data, count_cmd, garb, status);
		if (inf_pip.path_cmd)
		{
			data->cmd[0] = inf_pip.path_cmd;
			execve(inf_pip.path_cmd, data->cmd, inf_pip.tab_envv);
			ft_free_all(*garb);
			exit(0);
		}
		if (access(data->cmd[0], X_OK ) == -1 )
		{
			if (!data->cmd[0])
				exit(1);
			perror("access");
			ft_free_all(*garb);
			exit(126);
		}
	}
	else
	{
		ft_free_all(*garb);
		exit(1);
	}
		
}

void ft_child(t_exec *data, t_list_env **env, t_info_pipe *inf_pip, int count_cmd, t_garbage **garb, int *status)
{
	if (inf_pip->pid == -1)
	{
		perror("fork");
		ft_free_all(*garb);
		exit(1);
	}
	else if (inf_pip->pid == 0)
	{
		if (inf_pip->in_fd != STDIN_FILENO)
		{
			dup2(inf_pip->in_fd, STDIN_FILENO);
			close(inf_pip->in_fd);
		}
		if (data->next != NULL)
		{
			dup2(inf_pip->fd[1], STDOUT_FILENO);
			close(inf_pip->fd[0]), close(inf_pip->fd[1]);
		}
		ft_exec_child(data, env, *inf_pip, count_cmd, garb, status);
	}
	else
	{
		if (data->next != NULL)
			close(inf_pip->fd[1]);
		if (inf_pip->in_fd != STDIN_FILENO)
			close(inf_pip->in_fd);
		if (data->next != NULL)
			inf_pip->in_fd = inf_pip->fd[0];
	}
}

void ft_plusieur_cmd(t_exec *data, t_list_env **env, t_info_pipe *inf_pip, int count_cmd, t_garbage **garb, int *status)
{
	while (data != NULL)
	{
		if (data->next != NULL)
		{
			if (pipe(inf_pip->fd) == -1)
			{
				perror("pipe");
				ft_free_all(*garb);
				exit(1);
			}
		}
		inf_pip->pid = fork();
		ft_child(data, env, inf_pip, count_cmd, garb, status);
		data = data->next;
		(inf_pip->i)++;
	}	
}

int ft_count_cmd(t_exec *data)
{
	int i;

	i = 0;
	while (data != NULL)
	{
		data = data->next;
		i++;
	}
	return i;
}

void ft_pipe(t_exec *data, t_list_env **env, t_garbage **garb)
{	
	t_info_pipe inf_pip;
	inf_pip.i = 0;
	inf_pip.j = 0;
	inf_pip.in_fd = STDIN_FILENO;
	inf_pip.in_bultin = 0;
	int status;
	status = 0;
	inf_pip.tab_envv = tab_env(*env, garb);
	if(count_cmd(data) == 1 && ft_strlen_argc(data->cmd) == 1 
		&& ft_strcmpp(data->cmd[0], "export") != 0 && is_built_in(data->cmd[0]) == 0)
	{
		ft_one_cmd(data, env, count_cmd(data), garb, &status);
		ft_exit_status(status , 1);
		return;
	}
	else if (count_cmd(data) == 1 && ft_strlen_argc(data->cmd) != 1 && is_built_in(data->cmd[0]) == 0)
	{
		ft_one_cmd(data, env, count_cmd(data), garb, &status);
		ft_exit_status(status , 1);
		return;
	}
	else
	{
		ft_plusieur_cmd(data, env, &inf_pip, count_cmd(data), garb, &status);
	}
	waitpid(inf_pip.pid, &status, 0);
	if (WIFEXITED(status))
	{
		ft_exit_status(WEXITSTATUS(status) , 1);
	}
	else if (WIFSIGNALED(status))
	{
		ft_exit_status(WEXITSTATUS(status) + 130 , 1);
	}
    while(inf_pip.j < inf_pip.i)
    {
		wait(NULL);
		(inf_pip.j)++;
    }
}
