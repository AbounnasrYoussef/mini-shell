/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cherche_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:06:32 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/07 16:55:54 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_concat(char *str, char *str2, t_garbage **garb)
{
	int		i;
	int		j;
	char	*new_str;

	(void)garb;
	if (str == NULL)
		return (str2);
	if (str2 == NULL)
		return (str);
	new_str = ft_malloc(garb, (ft_strlenn(str) + ft_strlenn(str2) + 1));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	while (str2[j] != '\0')
	{
		new_str[i] = str2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	is_espace_tabulion(char *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return (1);
	while (cmd[i] != '\0')
	{
		if (cmd[i] != ' ' && cmd[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

void	error_cherch_path(char *cmd, t_garbage **garb)
{
	write(2, cmd, ft_strlenn(cmd));
	write(2, ": command not found\n", 20);
	ft_free_all(*garb);
	exit(127);
}

char 	*cherch_path2(t_exec *data, char *cmd, t_list_env **env, char *path, int count_cmd, t_garbage **garb)
{
	char	**paths;
	char	*path_cmd;
	int		i;

	i = 0;
	path_cmd = NULL;
	paths = ft_splitt(path, ':', garb);
	while (paths && paths[i] && (paths[i] != NULL))
	{
		paths[i] = ft_concat(paths[i], "/", garb);
		paths[i] = ft_concat(paths[i], cmd, garb);
		if (access(paths[i], X_OK) == 0)
		{
			path_cmd = paths[i];
			break ;
		}
		i++;
	}
	if (path_cmd == NULL && ft_built_in(data, env, count_cmd, garb) == -1)
		error_cherch_path(cmd, garb);
	return (path_cmd);
}

char	*cherch_path1(t_exec *data, char *cmd, t_list_env **env, int count_cmd, t_garbage **garb)
{
	char	*path;

	path = NULL;
	while (*env != NULL)
	{
		if (ft_strcmpp((*env)->variable, "PATH") == 0)
		{
			path = (*env)->val;
			break ;
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
	return (cherch_path2(data, cmd, env, path, count_cmd, garb));
}

char	*cherch_path(char *cmd, t_list_env **env, t_exec *data, int count_cmd, t_garbage **garb)
{
	if (is_espace_tabulion(cmd) == 0)
		error_cherch_path(cmd, garb);
	if (!cmd || !cmd[0])
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	return (cherch_path1(data, cmd, env, count_cmd, garb));
}
