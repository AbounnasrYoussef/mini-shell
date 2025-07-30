/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/30 16:55:00 by yabounna         ###   ########.fr       */
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
		setup_signals();
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

		expand_all_tokens(&token, last_exit_code, *env, &garb);
		*data = parse_tokens_to_exec_list(token, &garb);
		 t_exec *tmp = *data;
		// ft_pipe(ft_count_cmd(tmp), tmp, *env);
		
int i = 1;

while (tmp)
{
   printf("---- Commande %d ----\n", i);

   // Afficher les mots de la commande
   if (tmp->cmd)
   {
       for (int j = 0; tmp->cmd[j]; j++)
           printf("cmd[%d] = %s\n", j, tmp->cmd[j]);
       //     printf("%s", tmp->cmd[j]);
       // printf("\n");
   }

   // Afficher les redirections
   t_file *file = tmp->files;
   while (file)
   {
       printf("Redirection type: %d, file: %s\n", file->type, file->file_name);
       file = file->next;
   }

   tmp = tmp->next;
   i++;
}
       // if (*data != NULL)
       // {
       //     free_exec_list(*data); // Fonction à écrire pour libérer la liste t_exec
       //     *data = NULL;
       // }
       // Exécution des commandes et récupération du code de sortie
        
       // Nettoyage mémoire via garbage collector
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
