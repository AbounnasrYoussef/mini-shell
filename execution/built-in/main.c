/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:03:04 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/29 15:25:23 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <errno.h>
void ft_print_env_ex(t_list_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "_") != 0)
		{
			if (env->valeur_vari != NULL)
				printf("declare -x %s=\"%s\"\n", env->variable, env->valeur_vari);
			else
				printf("declare -x %s\n", env->variable);
		}
		env = env->next;
	}
}

void ft_print_env(t_list_env *env)
{
	while (env != NULL)
	{
		if (env->valeur_vari != NULL)
			printf("%s=\"%s\"\n", env->variable, env->valeur_vari);
		env = env->next;
	}
}

t_list_env *supp_var_nv(t_list_env *env)
{
	
	t_list_env *tmp;
	t_list_env *tmp2;
	
	tmp = env;
	tmp2 = env;
	
	while (env != NULL)
	{
		if (env->valeur_vari == NULL && ft_strcmpp(env->variable, "VSCODE_GIT_ASKPASS_EXTRA_ARGS") != 0)
		{
			tmp = ft_supp_arg(tmp, env->variable);
		}
		env = env->next;
	}
	return tmp;
}

int ft_built_in(int argc, t_exec *data, t_list_env *env)
{
	
	
	int len;
	if (argc > 1)
		len = ft_strlenn(data->cmd[0]) - 1;
	if (ft_strcmpp(data->cmd[0], "cd") == 0)
	{
		return (ft_cd(data->cmd, env), 0);
	}
	else if (ft_strcmpp(data->cmd[0], "pwd") == 0)
		return (printf("%s\n", ft_pwd(env)), 0);
	else if (ft_strcmpp(data->cmd[0], "echo") == 0)
		return (ft_echo(data->cmd), 0);
	else if (ft_strcmpp(data->cmd[0], "exit") == 0)
		return (ft_exit (len, data->cmd), 0);
	else if (ft_strcmpp(data->cmd[0], "export") == 0)
		return (ft_export(env, data->cmd), 0);
	else if (ft_strcmpp(data->cmd[0], "env") == 0)
	{
		if (argc == 1)
			return (ft_print_env(env), 0);
		else
		{
			write(2, "env: ", 5);
			write(2, data->cmd[1], ft_strlenn(data->cmd[1]));
			write(2, ": No such file or directory\n", 28);
			return 0;
		}
	}
	else if (ft_strcmpp(data->cmd[0], "unset") == 0)
		return (printf("djdjjd\n\n"), ft_unset(env, data->cmd), 0);
	
	return -1;
}



//int main(int argc, char **argv, char **env)
//{
//	t_list_env *envv;

//	envv = ft_envv(env);
//	if (argc > 1)
//		printf("aucun arg recommender");
//	else
//	{
//		while (1)
//		{
//			char *line = readline("minishell: ");
//			add_history(line);
//			if (!line || !*line)
//				continue ;
//			ft_built_in(line, envv);
//		}
//	}
//	return 0;
//}