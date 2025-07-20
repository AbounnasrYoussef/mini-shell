/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/20 11:11:08 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void ft_read_loop(t_list_env **env ,t_exec **data)
{
    char        *line;
    garbage   *garb;
    t_token     *token;
    int         last_exit_code = 0;
    while (1)
    {
        garb = NULL;
        line = readline("minishell$ ");
        if (!line)
            break; // Fin de l'entrée (Ctrl+D)
        if (*line)
            add_history(line); // Sauvegarde dans l'historique
        if (!syntaxe_errors(line))
        {
            free(line);
            continue;
        }
        token = tokens(line, &garb); // Tokenisation de la ligne
        free(line); // readline malloc => on libère après usage
        if (!token)
            continue;
        // Expansion des variables d'environnement et de $? sur les tokens
        expand_all_tokens(token, last_exit_code, *env, &garb);
        *data = parse_tokens_to_exec_list(token , &garb);
        t_exec *tmp = *data;
int i = 1;

while (tmp)
{
    printf("---- Commande %d ----\n", i);

    // Afficher les mots de la commande
    if (tmp->cmd)
    {
        for (int j = 0; tmp->cmd[j]; j++)
            printf("cmd[%d] = %s\n", j, tmp->cmd[j]);
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

int main(int ac, char **av, char **envp)
{
	t_list_env	*env_list;
	t_exec		*data;

	(void)ac;
	(void)av;

	data = NULL;

	env_list = ft_env(envp);

	ft_read_loop(&env_list ,&data);
    

	return (0);
}



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