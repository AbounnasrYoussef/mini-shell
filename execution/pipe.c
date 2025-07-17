/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:36:08 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/17 20:54:17 by arahhab          ###   ########.fr       */
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
//	char *argv1[] = {argv[1], NULL};
//	char *argv2[] = {argv[2], NULL};
//	char *argv3[] = {argv[3], NULL};
	
//	pip = pipe(fd);
//	int id;
//	int id2;
//	cmd = NULL;
//	cmd2 = NULL;
//	char *cmd3 = NULL;
//	if (argc > 2)
//	{
//		if (argv[1] != NULL)
//		{
//			cmd = cherche_path_cmd(argv[1], env);
//		}
//		if (argv[2] != NULL)
//		{
//			cmd2 = cherche_path_cmd(argv[2], env);
//		}
//	    if (argv[3] != NULL)
//		{
//			cmd3 = cherche_path_cmd(argv[3], env);
//		}
		
//		id = fork();
		
//		if (id == 0)
//		{
//			dup2(fd[1], STDOUT_FILENO);
//			close(fd[0]);
//			close(fd[1]);
//			execve(cmd, argv1, NULL);
//		}
//		if (id != 0)
//		{
//			waitpid(id, NULL, 0);
//		}
		
//		id2 = fork();
//		if (id2 == 0)
//		{
//			dup2(fd[0], STDIN_FILENO);
//			close(fd[0]);
//			close(fd[1]);
//			execve(cmd2, argv2, NULL);
//		}
		
//		if (id2 != 0)
//		{
//			waitpid(id2, NULL, 0);
//		}

//		int id3 = fork();
//		if (id3 == 0)
//		{
//			dup2(fd[0], STDIN_FILENO);
//			close(fd[0]);
//			close(fd[1]);
//			execve(cmd3, argv3, NULL);
//		}
		
//		if (id3 != 0)
//		{
//			waitpid(id3, NULL, 0);
//		}
//		//close(fd[0]);
//		//close(fd[1]);
//	}
//	else if (argc == 2)
//	{
//		if (argv[1] != NULL)
//		{
//			cmd = cherche_path_cmd(argv[1], env);
//		}
//		id = fork();
		
//		if (id == 0)
//		{
//			execve(cmd, argv1, NULL);
//		}
//		if (id != 0)
//		{
//			waitpid(id, NULL, 0);
//		}
//	}
	
//}




void ft_pipe(int argc, char **argv, char **env)
{
	char **cmd;
	int fd[argc - 1][2];
	int id[argc - 1];
	int pip;
	int i;
	int status;

	i = 0;
	
	cmd = malloc(argc * sizeof(char *));
	//while (i < (argc - 1))
	//{
	//	cmd[i] = malloc(2000);
	//	i++;
	//}
	i = 1;
	while (i < (argc))
	{
		cmd[i] = cherche_path_cmd(argv[i], env);
		i++;
	}
	
	i = 0;
	
	while (i < (argc))
	{
		pip = pipe(fd[i]);
		id[i] = fork();
	
		if (id[i] == 0)
		{
			char *argvv[] = {argv[i], NULL};
			if (i == 0)
				dup2(fd[i][1], STDOUT_FILENO);
			else if (i == argc - 1)
				dup2(fd[i][0], STDIN_FILENO);
			else
			{
				dup2(fd[i][0], STDIN_FILENO);
				dup2(fd[i][1], STDOUT_FILENO);
			}
			//close(fd[i][0]);
			//close(fd[i][1]);
			execve(cmd[i], argvv, NULL);
		}
		if (id[i] != 0)
		{
			waitpid(id[i], NULL, 0);
		}
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	ft_pipe(argc, argv, env);
}
