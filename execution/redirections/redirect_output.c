/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 05:54:12 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/17 07:29:25 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

#include <fcntl.h>




int main(int argc, char **argv, char **env)
{
	char *cmd;
	int fd[2];
	int fd2;
	char *buffer;
	int c;
	
	fd2 = open(argv[2], O_CREAT | O_RDWR);
	buffer = malloc(2000);
	int id;
	cmd = NULL;
	if (argv[1] != NULL)
	{
		cmd = cherche_path_cmd(argv[1], env);
	}

	
	id = fork();
	
	if (id == 0)
	{
		//c = read(fd[1], buffer, 2000);
		//printf("\n\n\n\n------- %s \n\n\n\n -------\n", buffer);
		execve(cmd, &argv[1], NULL);
		
	}
	if (id != 0)
	{
		wait(&id);
	}
	//write(fd2, buffer, 10);
	//printf("\n\n\n\n------- %s \n\n\n\n -------\n", buffer);
	
}
