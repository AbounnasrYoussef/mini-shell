/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/02 15:13:25 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_read()
{
    char *line;
    garbage *garb = NULL;
    t_token *token;
    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
            break; // if il y a un erreur 
        if (*line)
            add_history(line); // pour enregistrer tous les commande precedent
        if (syntaxe_errors(line) == 0)
            continue;
        token = tokens(line,&garb);
        if (token->value == WORD)
        {
            
        }
        free(line); // on free car readline il alloce 
    }
}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    ft_read();
    return 0;
}

//int main(int argc, char **argv, char **env)
//{
//	t_list *ls1 ;
//	ls1 = ft_env(env);
//	printf("%s", ls1->ligne);
//}