/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cherche_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:06:32 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/07 10:47:46 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char *ft_concat(char *str, char *str2, t_garbage **garb)
{
	int l1;
	int l2;
	int i;
	int j;
	char *new_str;
	(void)garb;
	if(str == NULL)
		return str2;
	if(str2 == NULL)
		return str;
	l1 = ft_strlenn(str);
	l2 = ft_strlenn(str2);
	new_str = ft_malloc(garb, (l1 + l2 + 1) * sizeof(char));
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

int is_espace_tabulion(char *cmd)
{
	int i;

	i = 0;
	if(cmd == NULL)
		return 1;
	while(cmd[i] != '\0')
	{
		if (cmd[i] != ' ' && cmd[i] != '\t')
			return 1;
		i++;
	}
	return 0;	
}

char *cherche_path_cmd(char *cmd, t_list_env **env, t_exec *data, int count_cmd, t_garbage **garb)
{
	
	char *path;
	char **paths;
	char *path_cmd;
	int i;
	
	path = NULL;
	path_cmd = NULL;
	i = 0;
	if (is_espace_tabulion(cmd) == 0)
	{
		write(2, cmd, ft_strlenn(cmd));
		write(2, ": command not found\n", 20);
		ft_free_all(*garb);
		exit(127);
	}
	if (!cmd || !cmd[0])
      return NULL;  
	if (access(cmd, X_OK) == 0)
        return cmd;
	if (cmd[0] == '/' || cmd[0] == '.') {
        if (access(cmd, X_OK) == 0)
            return cmd;
        return NULL;
    }
	while (*env != NULL)
	{
		if (ft_strcmpp((*env)->variable, "PATH") == 0)
		{
			path = (*env)->valeur;
			break;
		}
		(*env) = (*env)->next;
	}
	if (path == NULL)
	{
		if (access(cmd, X_OK) != 0)
		{
			perror("access");
			ft_free_all(*garb);
			exit(1);
		}
	}
	paths = ft_splitt(path, ':', garb);
	while (paths && paths[i] && (paths[i] != NULL))
	{
		paths[i] =  ft_concat(paths[i], "/", garb);
		paths[i] =  ft_concat(paths[i], cmd, garb);
		if (access(paths[i], X_OK) == 0)
		{
			path_cmd = paths[i];
			break;
		}
		i++;
	}
	if (path_cmd == NULL && ft_built_in(data, env, count_cmd, garb) == -1)
	{
		write(2, cmd, ft_strlenn(cmd));
		write(2, ": command not found\n", 20);
		ft_free_all(*garb);
		exit(127);
	}
	return path_cmd;
}