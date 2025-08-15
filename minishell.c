/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/15 11:15:09 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/execution.h"

int	g_handl_signals = 0;


void	ft_read_loop(char **envp, t_exec **data)
{
	char				*line;
	t_garbage			*garb;
	t_token				*token;
	int					last_exit_code;
	t_list_env			*env;
	t_parsing_context	ctx;

	last_exit_code = 0;
	env = ft_envvv(envp, &garb);
	if (envp[0] == NULL)
	{
		env = NULL;
		lst_add_back(&env, ft_lstnew("PATH", PATHD, &garb));
		lst_add_back(&env, ft_lstnew("PWD", getcwd(NULL, 0), &garb));
		lst_add_back(&env, ft_lstnew("SHLVL", "1", &garb));
		lst_add_back(&env, ft_lstnew("_", "/usr/bin/env", &garb));
	}
	while (1)
	{
		g_handl_signals = 0;
		save_terminal_settings();
		setup_signals();
		garb = NULL;
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		if (syntaxe_errors(line) == 0)
		{
			free(line);
			free_exec_list(*data);
			continue ;
		}
		token = tokens(line, &garb, &ctx);
		if (!token)
		{
			free(line);
			continue ;
		}
		expand_all_tokens(&token, last_exit_code, env, ctx);
		*data = parse_tokens_to_exec_list(token, &garb);
		if (!*data)
		{
			ft_free_all(garb);
			continue ;
		}
		if ((*data)->files != NULL)
		{
			process_heredocs(line, *data, env, &garb);
			if (g_handl_signals != 3)
				ft_exit_status(0, 1);
		}
		if (*data != NULL && g_handl_signals != 3)
		{
			ft_pipe(*data, &env, &garb);
			*data = NULL;
		}
	}
	ft_free_all(garb);
}

int	main(int ac, char **av, char **envp)
{
	t_exec		*data;

	(void)ac;
	(void)av;
	data = NULL;
	if (!isatty(0) || !isatty(1))
		return (1);
	ft_read_loop(envp, &data);
	return (0);
}
