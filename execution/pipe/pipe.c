/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:36:08 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/01 13:21:16 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include "../../minishell.h"

void ft_one_cmd(t_exec *data, int argc, t_list_env *env)
{
	int original_fd_in;
	int original_fd_out;
	
	if (is_espace_tabulion(data->cmd[0]) == 0)
	{
		write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
		write(2, ": command not found\n", 20);
	}
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

void ft_exec_child(t_exec *data, int argc, t_list_env *env, t_info_pipe inf_pip)
{
	if (data->files != NULL)
		ft_redirection(data);
	stat(data->cmd[0], &(inf_pip.info));
	if (S_ISDIR((inf_pip.info).st_mode))
	{
		if ((data->cmd[0][0] == '.' && data->cmd[0][1] == '/') || data->cmd[0][0] == '/')
		{
			write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
			(write(2, ": is a directory \n", 18), exit(1));
		}	
	}
	else if (!S_ISREG((inf_pip.info).st_mode) && is_slash(data->cmd[0]) == 0)
	{
		write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
		(write(2, ": No such file or directory\n", 28), exit(1));
	}
	inf_pip.in_bultin = ft_built_in(argc, data, env);
	if (inf_pip.in_bultin == -1)
	{
		inf_pip.path_cmd = cherche_path_cmd(data->cmd[0], env, argc, data);
		if (inf_pip.path_cmd)
			(execve(inf_pip.path_cmd, data->cmd, inf_pip.tab_envv), exit(1));
	}
	else
		exit(1);
}

void ft_child(t_exec *data, int argc, t_list_env *env, t_info_pipe *inf_pip)
{
	if (inf_pip->pid == -1)
		(perror("fork"), exit(1));
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
		ft_exec_child(data, argc, env, *inf_pip);
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

void ft_plusieur_cmd(t_exec *data, int argc, t_list_env *env, t_info_pipe *inf_pip)
{
	while (data != NULL)
	{
		if (data->next != NULL)
		{
			if (pipe(inf_pip->fd) == -1)
				(perror("pipe"), exit(1));
		}
		inf_pip->pid = fork();
		ft_child(data, argc, env, inf_pip);
		data = data->next;
		(inf_pip->i)++;
	}	
}

void ft_pipe(int argc, t_exec *data, t_list_env *env)
{	
	t_info_pipe inf_pip;
	
	inf_pip.i = 0;
	inf_pip.j = 0;
	inf_pip.in_fd = STDIN_FILENO;
	inf_pip.in_bultin = 0;
	inf_pip.tab_envv = tab_env(env);
	if(count_cmd(data) == 1 && ft_strlen_argc(data->cmd) == 1 
		&& ft_strcmpp(data->cmd[0], "export") != 0 && is_built_in(data->cmd[0]) == 0)
		ft_one_cmd(data, argc, env);
	else if (count_cmd(data) == 1 && ft_strlen_argc(data->cmd) != 1 && is_built_in(data->cmd[0]) == 0)
		ft_one_cmd(data, argc, env);
	else
	{
		ft_plusieur_cmd(data, argc, env, &inf_pip);
	}
    int status;
    while(inf_pip.j < inf_pip.i)
    {
        wait(&status);
		(inf_pip.j)++;
    }
}
