/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:36:08 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/29 16:05:48 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/stat.h>

char *ft_concat(char *str, char *str2)
{
	int l1;
	int l2;
	int i;
	int j;
	char *new_str;

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

char *cherche_path_cmd(char *cmd, t_list_env *env)
{
	
	char *path;
	char **paths;
	char *path_cmd;
	int i;
	char **cmd_n_op;
	struct stat info;
	
	cmd_n_op = ft_splitt(cmd, ' '); 
	path = NULL;
	i = 0;
	path_cmd = NULL;
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "PATH") == 0)
		{
			path = env->valeur_vari;
		}
		env = env->next;
	}
	if (path == NULL)
	{
		if (access(cmd, X_OK) == 0)
		{
			return cmd;
		}
	}
	paths = ft_splitt(path, ':');
	while (paths && paths[i] && (paths[i] != NULL))
	{
		paths[i] =  ft_concat(paths[i], "/");
		paths[i] =  ft_concat(paths[i], cmd_n_op[0]);
		if (access(paths[i], X_OK) == 0)
		{
			path_cmd = paths[i];
		}
		i++;
	}
	if (path_cmd == NULL)
	{
		if (path == NULL)
		{
			write(2, cmd, ft_strlenn(cmd));
			write(2, ": No such file or directory\n", 28);
		}
		else
		{
			write(2, cmd, ft_strlenn(cmd));
			write(2, ": command not found\n", 20);
		}
	
		//else if ((info.st_mode & S_IXUSR) == 0)
		//	printf("%s: Permission denied\n", cmd);
	}
	stat(path_cmd, &info);
	if (S_ISDIR(info.st_mode))
	{
		return NULL;
	}
	return path_cmd;
}

//int ft_exit_status(int status, int flags)
//{
//	static int exit_status;
//	if (flags)
//		exit_status = status;
//	return exit_status;
//}
void ft_pipe(int argc, t_exec *data, t_list_env *env)
{
	char **cmdd;
	int id[argc - 1];
	int i;
	int fd[2];
	int tmp[2];
	int c;
	struct stat info;
	t_list_env *debut_env;
	int d;
	int len;
	int status;
	
	c = 0;
	i = 0;
	cmdd = malloc(argc * sizeof(char *));
	fd[0] = 0;
	fd[1] = 1;
	tmp[0] = 0;
	tmp[1] = 1;
	debut_env = env;
	d = 0;
	len = 0;
	status = 0;
	while (i < argc) 
	{
	
		if (ft_strcmpp(data->cmd[0], "./minishell") == 0)
	    {
			
			while(debut_env != NULL)
			{
				
				if(ft_strcmpp(debut_env->variable, "PATH") == 0)
				{
					d = 1;
					env = supp_var_nv(env);
					if (data->next == NULL)
						return ;
				}
				debut_env = debut_env->next;
			}
			if (d == 1)
			{
				env = supp_var_nv(env);
				if (data->next == NULL)
					return ;
			}
			else
			{
				write(2, "./minishell: No such file or directory\n", 39);
				return ;
			}
	    }
		else if (ft_strcmpp(data->cmd[0], "exit") == 0 && argc == 1)
		{
			ft_exit (0, data->cmd);
		}
		pipe(fd);
		id[i] = fork();
		if (id[i] == 0)
		{
			
			dup2(tmp[0], STDIN_FILENO);
			if (i < argc - 1) {
				dup2(fd[1], STDOUT_FILENO);
			}
			close(fd[0]);
			close(fd[1]);
			if (tmp[0] != 0)
				close(tmp[0]);
			
			char **cmdv;
			cmdv = data->cmd;
			if (ft_built_in(argc, data, env) == -1)
			{
				stat(data->cmd[0], &info);
				if (S_ISDIR(info.st_mode))
				{
					if (data->cmd[0][0] == '.' && data->cmd[0][1] == '/')
					{
						write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
						write(2, ": is a directory \n", 18);
						if (argc == 1)
							return ;
					}
						
					else if (cherche_path_cmd((data->cmd[0]), env) == NULL)
					{
						write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
						write(2, ": is a directory \n", 18);
					}
				}
				if ((argc == 1) && (data->cmd[1] == NULL) && (cherche_path_cmd((data->cmd[0]), env) == NULL))
				{
					if (access(data->cmd[0], X_OK) == 0)
					{
						execve(data->cmd[0], cmdv, NULL);
					}
					return ;
				}
				else if ((argc == 1) && !(S_ISDIR(info.st_mode)) && data->cmd[0][0] == '.' && data->cmd[0][1] == '/')
				{
					if (!S_ISREG(info.st_mode))
					{
						write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
						write(2, ": No such file or directory\n", 28);
					}
				}
				else
				{
					
					cmdd[i] = cherche_path_cmd((data->cmd[0]), env);
					execve(cmdd[i], cmdv, NULL);

				}
			}
				
		}
		else
		{
			close(fd[1]);
			if (tmp[0] != 0) 
			{
				close(tmp[0]);
			}
			tmp[0] = fd[0];	
		}
		
		data = data->next;
		i++;
	}
	if (tmp[0] != 0)
	{
		close(tmp[0]);
	}
	while (c < argc)
	{
		//wait(NULL);
		waitpid(id[c], NULL, 0);
		//waitpid(id[c], &status, 0);
		//if (WIFEXITED(status) == 0)
		//{
		//	ft_exit_status(status, 1);
		//}
		c++;
	}
}

