/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/30 16:47:57 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../execution/execution.h"

// void ft_read()
// {
//     char *line;
//     garbage *garb = NULL;
//     t_token *token;
//     while (1)
//     {
//         line = readline("minishell$ ");
//         if (!line)
//             break; // if il y a un erreur 
//         if (*line)
//             add_history(line); // pour enregistrer tous les commande precedent
//         if (syntaxe_errors(line) == 0)
//             continue;
//         token = tokens(line,&garb);
//         free(line); // on free car readline il alloce 
//     }
// }
int ft_count_cmd(t_exec *data)
{
	int i;

	i = 0;
	while (data != NULL)
	{
		data = data->next;
		i++;
	}
	return i;
}

void ft_read_loop(t_list_env **env, t_exec **data)
{
    char        *line;
    garbage     *garb;
    t_token     *token;
    int         last_exit_code = 0;

    while (1)
    {
        garb = NULL;
        
        if (isatty(STDIN_FILENO))
            line = readline("minishell$ ");
        else
            line = get_next_line(STDIN_FILENO);
        if (!line)
        {
            if (isatty(STDIN_FILENO))
                write(1, "exit\n", 5);
            break;
        }
        if (*line)
            add_history(line);
        if (!syntaxe_errors(line))
        {
            ft_exit_status(258, 1);
            free(line);
            continue;
        }
        token = tokens(line, &garb);
        free(line);
        if (!token)
            continue;

        expand_all_tokens(&token, last_exit_code, *env, &garb);
        *data = parse_tokens_to_exec_list(token, &garb);
        
        if (*data != NULL)
        {
            ft_pipe(ft_count_cmd(*data), *data, *env);
            ft_free_all(garb);
            *data = NULL;
        }
    }
}


int main(int ac, char **av, char **envp)
{
	t_list_env	*env_list;
	//t_list_env	*debut;
	t_exec		*data;

	(void)ac;
	(void)av;

	data = NULL;

	env_list = ft_env(envp);

	ft_read_loop(&env_list ,&data);
    

	return (0);
}

//int main(int ac, char **av, char **envp)
//{
//	t_list_env	*env_list;
//	t_exec		*data;

//	(void)ac;
//	(void)av;

//	data = NULL;

//	env_list = ft_env(envp);

//	ft_read_loop(&env_list ,&data);
    

//	return (0);
//}



// void ft_read()
// {
//     char *line;
//     garbage *garb = NULL;
//     t_token *token;
//     while (1)
//     {
//         line = readline("minishell$ ");
//         if (!line)
//             break; // if il y a un erreur 
//         if (*line)
//             add_history(line); // pour enregistrer tous les commande precedent
//         if (syntaxe_errors(line) == 0)
//             continue;
//         token = tokens(line,&garb);
//         free(line); // on free car readline il alloce 
//     }
// }

// int main(int ac, char **av)
// {
//     (void)ac;
//     (void)av;
//     ft_read();
//     return 0;
// }