/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:36:08 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/25 19:50:57 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
		printf("%s: command not found\n", cmd);
		//exit(1);
	}
	return path_cmd;
}

void ft_pipe(int argc, t_exec *data, t_list_env *env)
{
	char **cmdd;
	int id[argc - 1];
	int i;
	int fd[2];
	int tmp[2];
	int c;
	
	c = 0;
	i = 0;
	cmdd = malloc(argc * sizeof(char *));
	fd[0] = 0;
	fd[1] = 1;
	tmp[0] = 0;
	tmp[1] = 1;
	while (i < argc) 
	{
		if (ft_strcmpp(data->cmd[0], "./minishell") == 0)
	    {
			env = supp_var_nv(env);
			return ;
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
			if (ft_built_in(data, env) == -1)
			{
				cmdd[i] = cherche_path_cmd((data->cmd[0]), env);
				execve(cmdd[i], cmdv, NULL);
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
		waitpid(id[c], NULL, 0);
		c++;
	}
}


//int main(int argc, char **argv, char **env)
//{
//	ft_pipe(argc, argv, env);
//}
