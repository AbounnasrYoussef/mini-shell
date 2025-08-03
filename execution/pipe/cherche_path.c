/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cherche_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:06:32 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/03 13:38:20 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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

int is_espace_tabulion(char *cmd)
{
	int i;

	i = 0;
	while(cmd[i] != '\0')
	{
		if (cmd[i] != ' ' && cmd[i] != '\t')
			return 1;
		i++;
	}
	return 0;	
}

char *cherche_path_cmd(char *cmd, t_list_env **env, t_exec *data, int count_cmd)
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
		exit(1);
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
			path = (*env)->valeur_vari;
			break;
		}
		(*env) = (*env)->next;
	}
	if (path == NULL)
	{
		write(2, cmd, ft_strlenn(cmd));
		write(2, ": No such file or directory\n", 28);
		exit(1);
	}
	paths = ft_splitt(path, ':');
	while (paths && paths[i] && (paths[i] != NULL))
	{
		paths[i] =  ft_concat(paths[i], "/");
		paths[i] =  ft_concat(paths[i], cmd);
		if (access(paths[i], X_OK) == 0)
		{
			path_cmd = paths[i];
			break;
		}
		i++;
	}
	if (path_cmd == NULL && ft_built_in(data, env, count_cmd) == -1)
	{
		write(2, cmd, ft_strlenn(cmd));
		write(2, ": command not found\n", 20);
		exit(1);
	}
	return path_cmd;
}