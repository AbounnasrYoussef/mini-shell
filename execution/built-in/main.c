/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:03:04 by arahhab           #+#    #+#             */
/*   Updated: 2025/07/15 15:00:36 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_print_env_ex(t_list *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->variable, "_") != 0)
		{
			if (env->valeur_vari != NULL)
				printf("declare -x %s=\"%s\"\n", env->variable, env->valeur_vari);
			else
				printf("declare -x %s\n", env->variable);
		}
		env = env->next;
	}
}

void ft_print_env(t_list *env)
{
	while (env != NULL)
	{
		if (env->valeur_vari != NULL)
			printf("%s=\"%s\"\n", env->variable, env->valeur_vari);
		env = env->next;
	}
}

void ft_built_in(char *line, t_list *env)
{
	char **args;
	int argc;
	int len;
	
	args = NULL;
	args = ft_split(line, ' ');
	argc = ft_strlen_argc(args);
	if (argc > 1)
		len = ft_strlen(args[1]) - 1;
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args, line, env);
	else if (ft_strcmp(args[0], "pwd") == 0)
		printf("%s\n", ft_pwd());
	else if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(argc, args);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit (len, argc, args);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(env, args, argc);
	else if (ft_strcmp(args[0], "env") == 0)
	{
		if (argc == 1)
			ft_print_env(env);
		else
			printf("env: %s: No such file or directory\n", args[1]);
	}
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(env, args);
}

int main(int argc, char **argv, char **env)
{
	t_list *envv;

	envv = ft_env(env);
	if (argc > 1)
		printf("aucun arg recommender");
	else
	{
		while (1)
		{
			char *line = readline("minishell: ");
			add_history(line);
			if (!line || !*line)
				continue ;
			ft_built_in(line, envv);
		}
	}
	return 0;
}