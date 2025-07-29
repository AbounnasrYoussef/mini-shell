/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 16:28:03 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_read_loop(t_list_env **env, t_exec **data)
{
	char	*line;
	garbage	*garb;
	t_token	*token;
	int		last_exit_code;

	(void)env;
	(void)data;
	last_exit_code = 0;
	while (1)
	{
		garb = NULL;
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		if (!syntaxe_errors(line))
		{
			free(line);
			continue ;
		}
		token = tokens(line, &garb);
		free(line);
		if (!token)
			continue ;
		t_token *tmp = token;
		while (tmp)
		{
    		printf("%s\n", tmp->value);
    		tmp = tmp->next;
		}

		// expand_all_tokens(&token, last_exit_code, *env, &garb);
		// *data = parse_tokens_to_exec_list(token, &garb);
		ft_free_all(garb);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_list_env	*env_list;
	t_exec		*data;

	(void)ac;
	(void)av;
	data = NULL;
	env_list = ft_env(envp);
	ft_read_loop(&env_list, &data);
	return (0);
}
