/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/19 22:57:26 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/execution.h"

int	g_handl_signals = 0;

void	env_i_and_readline(char **envp, t_read_loop *inf_read, int flag)
{
	char	**str;

	str = ft_malloc(&(*inf_read).garb, 6 * sizeof(char *));
	if (flag == 0)
	{
		str[0] = PATHD;
		str[1] = ft_concat("PWD=", getcwd(NULL, 0), &(*inf_read).garb);
		str[2] = "SHLVL = 1";
		str[3] = "_=/usr/bin/env";
		str[4] = "OLDPWD";
		str[5] = NULL;
		if (envp[0] == NULL)
			(*inf_read).env = ft_envvv(str, &(*inf_read).garb);
		else
			(*inf_read).env = ft_envvv(envp, &((*inf_read).garb));
	}
	else if (flag == 1)
	{
		g_handl_signals = 0;
		save_terminal_settings();
		setup_signals();
		(*inf_read).garb = NULL;
		(*inf_read).line = readline("minishell$ ");
	}
}

void	ft_herdoc_piepe(t_exec **data, t_read_loop *inf_read)
{
	process_heredocs((*inf_read).line, *data,
		(*inf_read).env, &(*inf_read).garb);
	if (g_handl_signals != 3)
		ft_exit_status(0, 1);
	if (*data != NULL && g_handl_signals != 3)
	{
		ft_pipe(*data, &(*inf_read).env, &(*inf_read).garb);
		*data = NULL;
	}
}

int	ft_parsing(t_exec **data, t_read_loop inf_read, int flag)
{
	if (flag == 0)
	{
		if (syntaxe_errors((inf_read).line) == 0)
		{
			(free((inf_read).line), free_exec_list(*data));
			return (0);
		}
	}
	else if (flag == 1)
	{
		if (!inf_read.token)
		{
			free(inf_read.line);
			return (0);
		}
	}
	else if (flag == 2)
	{
		if (!*data)
		{
			ft_free_all(inf_read.garb);
			return (0);
		}
	}
	return (1);
}

void print_token(const t_token *token) {
    if (!token) {
        printf("Token: (null)\n");
        return;
    }
    printf("  value: [%s]\n", token->value ? token->value : "(null)");
    printf("  type: %d\n", token->type);
    printf("  quoted: %d\n", token->quoted);
    printf("  double_quote: %d\n", token->double_quote);
    printf("  join: %d\n", token->join);
    printf("  next: %p\n", (void*)token->next);
}

void print_token_list(const t_token *head) {
    int i = 0;
    while (head) {
        printf("Token #%d:\n", i++);
        print_token(head);
        head = head->next;
    }
}

void	ft_read_loop(char **envp, t_exec **data)
{
	t_read_loop	inf_read;

	inf_read.i = 3;
	env_i_and_readline(envp, &inf_read, 0);
	while (1)
	{	
		env_i_and_readline(envp, &inf_read, 1);
		if (!inf_read.line)
			break ;
		if (*inf_read.line)
			add_history(inf_read.line);
		if (ft_parsing(data, inf_read, 0) == 0)
			continue ;
		inf_read.token = tokens(inf_read.line, &inf_read.garb, &inf_read.ctx);
		if (ft_parsing(data, inf_read, 1) == 0)
			continue ;
		norm_read_loop(data, inf_read);
		if (ft_parsing(data, inf_read, 2) == 0)
			continue ;
		ft_herdoc_piepe(data, &inf_read);
		while (inf_read.i < 1024)
		{
			close(inf_read.i);
			inf_read.i++;
		}
	}

	ft_free_all(inf_read.garb);	
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
	write(1, "exit\n", 5);
	return (ft_exit_status(0, 0));
}
