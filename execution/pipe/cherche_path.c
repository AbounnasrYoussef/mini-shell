/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cherche_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:06:32 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/07 18:38:16 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*cherch_path2(t_exec *data, t_list_env **env, t_inf_cher_path inf_path
	, t_garbage **garb)
{
	char	**paths;
	char	*path_cmd;
	int		i;

	i = 0;
	path_cmd = NULL;
	paths = ft_splitt(inf_path.path, ':', garb);
	while (paths && paths[i] && (paths[i] != NULL))
	{
		paths[i] = ft_concat(paths[i], "/", garb);
		paths[i] = ft_concat(paths[i], data->cmd[0], garb);
		if (access(paths[i], X_OK) == 0)
		{
			path_cmd = paths[i];
			break ;
		}
		i++;
	}
	if (path_cmd == NULL && ft_built_in(data, env, inf_path.c_cmd, garb) == -1)
		error_cherch_path(data->cmd[0], garb);
	return (path_cmd);
}

char	*cherch_path1(t_exec *data, t_list_env **env, int count_cmd
		, t_garbage **garb)
{
	t_inf_cher_path	inf_path;

	inf_path.path = NULL;
	inf_path.c_cmd = count_cmd;
	while (*env != NULL)
	{
		if (ft_strcmpp((*env)->variable, "PATH") == 0)
		{
			inf_path.path = (*env)->val;
			break ;
		}
		(*env) = (*env)->next;
	}
	if (inf_path.path == NULL)
	{
		if (access(data->cmd[0], X_OK) != 0)
		{
			perror("access");
			ft_free_all(*garb);
			exit(1);
		}
	}
	return (cherch_path2(data, env, inf_path, garb));
}

char	*cherch_path(t_list_env **env, t_exec *data, int count_cmd
		, t_garbage **garb)
{
	if (is_espace_tabulion(data->cmd[0]) == 0)
		error_cherch_path(data->cmd[0], garb);
	if (!data->cmd[0] || !data->cmd[0][0])
		return (NULL);
	if (access(data->cmd[0], X_OK) == 0)
		return (data->cmd[0]);
	if (data->cmd[0][0] == '/' || data->cmd[0][0] == '.')
	{
		if (access(data->cmd[0], X_OK) == 0)
			return (data->cmd[0]);
		return (NULL);
	}
	return (cherch_path1(data, env, count_cmd, garb));
}
