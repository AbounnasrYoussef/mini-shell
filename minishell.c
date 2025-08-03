/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/03 17:46:54 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/execution.h"

int	g_exit_status = 0;

void	ft_read_loop(t_list_env **env, t_exec **data)
{
	char		*line;
	t_garbage		*garb;
	t_token		*token;
	int			last_exit_code = 0;

	setup_signals();
	while (1)
	{
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
		token = tokens(line, &garb);
		free(line);
		if (!token)
		{
			continue ;
		}

		expand_all_tokens(&token, last_exit_code, *env, &garb);
		*data = parse_tokens_to_exec_list(token, &garb);
		if (!*data)
		{
			ft_free_all(garb);
			continue;
		}

		// 👇 heredoc traité ici AVANT exécution
		process_heredocs(*data, *env, &garb);


		// 🔍 Debug - Afficher les commandes et redirections
		// printf("%d\n",ft_count_cmd(*data));
		if (*data != NULL)
        {
            //printf("%d\n\n", ft_count_cmd(*data));
			ft_pipe(*data, env);
            ft_free_all(garb);
            *data = NULL;
        }
		// t_exec *tmp = *data;
		// int i = 1;
		// while (tmp)
		// {
		// 	printf("---- Commande %d ----\n", i);
		// 	if (tmp->cmd)
		// 	{
		// 		for (int j = 0; tmp->cmd[j]; j++)
		// 			printf("cmd[%d] = '%s'\n", j, tmp->cmd[j]);
		// 	}

		// 	t_file *file = tmp->files;
		// 	while (file)
		// 	{
		// 		printf("Redirection type: %d, file: %s\n", file->type, file->file_name);
		// 		file = file->next;
		// 	}
		// 	tmp = tmp->next;
		// 	i++;
		// }


		// 🧹 Nettoyage mémoire
		//ft_free_all(garb);
		//free_exec_list(*data); *data = NULL;
	}
}


// void	ft_read_loop(t_list_env **env, t_exec **data)
// {
// 	char	*line;
// 	garbage	*garb;
// 	t_token	*token;
// 	int		last_exit_code;

// 	(void)env;
// 	(void)data;
// 	last_exit_code = 0;
// 	while (1)
// 	{
// 		// setup_signals();
// 		garb = NULL;
// 		line = readline("minishell$ ");
// 		if (!line)
// 			break ;
// 		if (*line)
// 			add_history(line);
// 		if (!syntaxe_errors(line))
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		token = tokens(line, &garb);
// 		free(line);
// 		if (!token)
// 			continue ;

// 		expand_all_tokens(&token, last_exit_code, *env, &garb);
// 		*data = parse_tokens_to_exec_list(token, &garb);
// 		process_heredocs(*data, *env, &garb);
// 		t_exec *tmp = *data;
// 		// ft_pipe(ft_count_cmd(tmp), tmp, *env);
		
// int i = 1;

// while (tmp)
// {
//    printf("---- Commande %d ----\n", i);

//    // Afficher les mots de la commande
//    if (tmp->cmd)
//    {
//        for (int j = 0; tmp->cmd[j]; j++)
//            printf("cmd[%d] = %s\n", j, tmp->cmd[j]);
//        //     printf("%s", tmp->cmd[j]);
//        // printf("\n");
//    }

//    // Afficher les redirections
//    t_file *file = tmp->files;
//    while (file)
//    {
//        printf("Redirection type: %d, file: %s\n", file->type, file->file_name);
//        file = file->next;
//    }

//    tmp = tmp->next;
//    i++;
// }
//        // if (*data != NULL)
//        // {
//        //     free_exec_list(*data); // Fonction à écrire pour libérer la liste t_exec
//        //     *data = NULL;
//        // }
//        // Exécution des commandes et récupération du code de sortie
        
//        // Nettoyage mémoire via garbage collector
// 		ft_free_all(garb);
// 	}
// }




int	main(int ac, char **av, char **envp)
{
	t_list_env	*env_list;
	t_exec		*data;

	(void)ac;
	(void)av;
	data = NULL;
	if (!isatty(0) || !isatty(1))
		return 1;
	env_list = ft_envvv(envp);
	if (env_list == NULL)
	{
		ft_lstadd_backk(&env_list, ft_lstneww("PATH", "/bin/:/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
		ft_lstadd_backk(&env_list, ft_lstneww("PWD", getcwd(NULL, 0)));
		ft_lstadd_backk(&env_list, ft_lstneww("_", "/usr/bin/env"));
	}
	ft_read_loop(&env_list, &data);
	return (0);
}
