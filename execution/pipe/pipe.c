/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:36:08 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/31 17:27:08 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include "../../minishell.h"

char *ft_concat(char *str, char *str2)
{
	int l1;
	int l2;
	int i;
	int j;
	char *new_str;

	if(str == NULL)
		return str2;
	if(str2 == NULL)
		return str;
	l1 = ft_strlenn(str);
	l2 = ft_strlenn(str2);
	new_str = malloc((l1 + l2 + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	while(str2[j] != '\0')
	{
		new_str[i] = str2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return new_str;
}

char *cherche_path_cmd(char *cmd, t_list_env *env, int argc, t_exec *data)
{
	
	char *path;
	char **paths;
	char *path_cmd;
	int i;
	char *cmd_n_op;
	
	path = NULL;
	path_cmd = NULL;
	i = 0;
	if (!cmd || !cmd[0])
        return NULL;
	if (cmd[0] == '/' || cmd[0] == '.') {
        if (access(cmd, X_OK) == 0)
            return cmd;
        return NULL;
    }
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "PATH") == 0)
		{
			path = env->valeur_vari;
			break;
		}
		env = env->next;
	}
	if (path == NULL)
	{
		write(2, cmd, ft_strlenn(cmd));
		write(2, ": No such file or directory\n", 28);
		exit(1);
	}
	cmd_n_op = ft_splitt(cmd, ' ')[0]; 
	paths = ft_splitt(path, ':');
	while (paths && paths[i] && (paths[i] != NULL))
	{
		paths[i] =  ft_concat(paths[i], "/");
		paths[i] =  ft_concat(paths[i], cmd_n_op);
		if (access(paths[i], X_OK) == 0)
		{
			path_cmd = paths[i];
			break;
		}
		i++;
	}
	if (path_cmd == NULL && ft_built_in(argc, data, env) == -1)
	{
		write(2, cmd, ft_strlenn(cmd));
		write(2, ": command not found\n", 20);
		exit(1);
	}
	return path_cmd;
}

int is_slash(char *str)
{
	int i;
	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '/')
		{
			return 0;
		}
		i++;
	}
	return 1;
}

int count_cmd(t_exec *data)
{
	int i;
	i = 0;

	while(data != NULL)
	{
		data = data->next;
		i++;
	}
	return i; 
}

int is_built_in(char *str)
{
	if(ft_strcmpp(str, "export") == 0)
		return 0;
	else if(ft_strcmpp(str, "cd") == 0)
		return 0;
	else if(ft_strcmpp(str, "echo") == 0)
		return 0;
	else if(ft_strcmpp(str, "env") == 0)
		return 0;
	else if(ft_strcmpp(str, "exit") == 0)
		return 0;
	else if(ft_strcmpp(str, "pwd") == 0)
		return 0;
	else if(ft_strcmpp(str, "unset") == 0)
		return 0;
	return -1;
}

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
			fd_herdoc = (int)ft_atoi(ft_strlenn(file->file_name), file->file_name);
			printf("%d\n\n", fd_herdoc);
			dup2(fd_herdoc, STDIN_FILENO);
			close(fd_herdoc);
		}
		file = file->next;
	}
	
}

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
	
	j = 0;
	in_fd = STDIN_FILENO;
	i = 0;
	in_bultin = 0;
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
						execve(path_cmd, data->cmd, NULL); 
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
