/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:36:08 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/18 15:36:04 by arahhab          ###   ########.fr       */
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

	l1 = ft_strlen(str);
	l2 = ft_strlen(str2);
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

char *cherche_path_cmd(char *cmd, char **env)
{
	t_list *envv;
	char *path;
	char **paths;
	char *path_cmd;
	int i;
	char **cmd_n_op;
	
	cmd_n_op = ft_split(cmd, ' '); 
	envv = ft_env(env);
	path = NULL;
	i = 0;
	path_cmd = NULL;
	while (envv != NULL)
	{
		if (ft_strcmp(envv->variable, "PATH") == 0)
		{
			path = envv->valeur_vari;
		}
		
		envv = envv->next;
	}
	paths = ft_split(path, ':');
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
		exit(1);
	}
	return path_cmd;
}

void ft_pipe(int argc, char **argv, char **env)
{
	char **cmd;
	int id[argc - 1];
	int pip;
	int i;
	int fd[2];
	int tmp[2];
	int c;
	
	c = 0;
	i = 0;
	cmd = malloc(argc * sizeof(char *));
	fd[0] = 0;
	fd[1] = 1;
	tmp[0] = 0;
	tmp[1] = 1;
	while (i < argc) {
		if (i < argc - 1)
		{
			cmd[i] = cherche_path_cmd(argv[i + 1], env);
			//printf("%s \n\n", argv[i + 1]);
		}
		pipe(fd);
		id[i] = fork();
		if (id[i] == 0) {
			dup2(tmp[0], STDIN_FILENO);
			if (i < argc -1) {
				dup2(fd[1], STDOUT_FILENO);
			}
			close(fd[0]);
			close(fd[1]);
			if (tmp[0] != 0)
				close(tmp[0]);
			char **cmdv;
			cmdv = ft_split(argv[i], ' '); 
			execve(cmd[i - 1], cmdv, NULL);
		}
		else
		{
			close(fd[1]);
			if (tmp[0] != 0) {
				close(tmp[0]);
			}
			tmp[0] = fd[0];	
		}
		i++;
	}
	if (tmp[0] != 0)
	{
		close(tmp[0]);
	}
	while (c < argc - 1)
	{
		waitpid(id[c], NULL, 0);
		c++;
	}
}


//int main(int argc, char **argv, char **env)
//{
//	ft_pipe(argc, argv, env);
//}
