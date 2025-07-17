/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:36:08 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/17 04:33:13 by arahhab          ###   ########.fr       */
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
	
	envv = ft_env(env);
	path = NULL;
	i = 0;
	
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
		paths[i] =  ft_concat(paths[i], cmd);
		if (access(paths[i], X_OK) == 0)
		{
			path_cmd = paths[i];
		}
		i++;
	}
	return path_cmd;
}


//int main(int argc, char **argv, char **env)
//{
//	int n = 1;
	
//	int id;

//	id = fork();
//	if (id == 0)
//	{
//		n = 9;
//	}
//	else
//	{
//		n = 100;
//	}
//	if (id != 0)
//	{
//		wait(NULL);
//	}
//	printf("%d \n", n);
	
//}





//int main(int argc, char **argv, char **env)
//{
//	char *cmd;
//	char *cmd2;
//	int fd[2];
//	int pip;
	
//	pip = pipe(fd);
//	int id;
//	int id2;
//	cmd = NULL;
//	if (argv[1] != NULL)
//	{
//		cmd = cherche_path_cmd(argv[1], env);
//	}
//	if (argv[2] != NULL)
//	{
//		cmd2 = cherche_path_cmd(argv[2], env);
//	}
	
//	id = fork();
	
//	if (id == 0)
//	{
//		dup2(fd[0], STDIN_FILENO);
//		close(fd[1]);
//		close(fd[0]);
//		execve(cmd, &argv[1], NULL);
//	}
//	if (id != 0)
//	{
//		wait(NULL);
//	}
	
//	id2 = fork();
//	if (id2 == 0)
//	{
//		dup2(fd[1], STDOUT_FILENO);
//		close(fd[1]);
//		close(fd[0]);
//		execve(cmd2, &argv[2], NULL);
//	}
	
//	if (id2 != 0)
//	{
//		wait(NULL);
//	}
//}




void ft_pipe(int argc, char **argv, char **env)
{
	char **cmd;
	int fd[2];
	int id[argc - 1];
	int pip;
	int i;
	
	i = 0;
	pip = pipe(fd);
	cmd = malloc(200);
	while (i < (argc - 1))
	{
		cmd[i] = malloc(200);
		i++;
	}
	i = 1;
	while (i < (argc))
	{
		cmd[i] = cherche_path_cmd(argv[i], env);
		i++;
	}
	
	i = 1;

	while (i < (argc))
	{
		id[i] = fork();
	
		if (id[i] == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			close(fd[0]);
			execve(cmd[i], &argv[1], NULL);
		}
		if (id[i] != 0)
		{
			wait(NULL);
		}
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	ft_pipe(argc, argv, env);
}
