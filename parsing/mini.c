/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/17 10:49:01 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_read_loop(t_list_env *env)
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
        if (!tokens)
            continue;
        // Expansion des variables d'environnement et de $? sur les tokens
        expand_all_tokens(token, last_exit_code, env, &garb);
        // Exécution des commandes et récupération du code de sortie
        last_exit_code = execute(token, env, &garb);
        // Nettoyage mémoire via garbage collector
        ft_free_all(&garb);
    }
}

// Entrée du programme
int main(int ac, char **av, char **envp)
{
    t_list_env *env_list;

    (void)ac;
    (void)av;

    // Initialiser l'environnement en liste chaînée
    env_list = init_env(envp);

    // Lancer la boucle principale
    ft_read_loop(env_list);

    return 0;
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