/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:03:04 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/07 16:55:54 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	error_env(char *str)
{
	write(2, "env: ", 5);
	write(2, str, ft_strlenn(str));
	write(2, ": No such file or directory\n", 28);
	exit(127);
}

int	check_exist_pwd(t_list_env *env)
{
	t_list_env	*copy_env;

	copy_env = env;
	while (copy_env)
	{
		if (ft_strcmpp(copy_env->variable, "PWD") == 0)
		{
			return (0);
		}
		copy_env = copy_env->next;
	}
	return (1);
}

void	ft_change_oldpwd(t_list_env **env)
{
	t_list_env	*copy_env;

	copy_env = *env;
	while (copy_env)
	{
		if (ft_strcmpp(copy_env->variable, "OLDPWD") == 0)
		{
			copy_env->val = "";
		}
		copy_env = copy_env->next;
	}
}

int	help_built(t_exec *data, t_list_env **env
		, t_exit inf_exit, t_garbage **garb)
{
	if (data->cmd[1] != NULL)
		inf_exit.len = ft_strlenn(data->cmd[1]) - 1;
	if (ft_strcmpp(data->cmd[0], "pwd") == 0)
		return (printf("%s\n", ft_pwd(*env)), 0);
	else if (ft_strcmpp(data->cmd[0], "echo") == 0)
		return (ft_echo(data->cmd), 0);
	else if (ft_strcmpp(data->cmd[0], "exit") == 0)
		return (ft_exit (inf_exit, data->cmd, garb), 0);
	else if (ft_strcmpp(data->cmd[0], "export") == 0)
		return (ft_export(*env, data->cmd, garb), 0);
	else if (ft_strcmpp(data->cmd[0], "env") == 0)
	{
		if (data->cmd[1] == NULL)
			return (ft_print_env(*env), 0);
		else
			return (error_env(data->cmd[1]), 0);
	}
	else if (ft_strcmpp(data->cmd[0], "unset") == 0)
	{
		ft_unset(env, data->cmd);
		if (check_exist_pwd(*env) == 1)
			ft_change_oldpwd(env);
		return (0);
	}
	return (-1);
}

int	ft_built_in(t_exec *data, t_list_env **env, int count_cmd, t_garbage **garb)
{
	int		len;
	t_exit	inf_exit;

	len = 0;
	inf_exit.c_cmd = count_cmd;
	if (data->cmd[0] == NULL)
		return (-1);
	if (ft_strcmpp(data->cmd[0], "cd") == 0)
		return (ft_cd(data->cmd, *env), 0);
	return (help_built(data, env, inf_exit, garb));
}
