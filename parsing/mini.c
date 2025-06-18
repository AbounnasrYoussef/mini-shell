/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/18 09:54:11 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_read()
{
    char *line;

    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
            break; // if il y a un erreur 
        if (*line)
            add_history(line); // pour enregistrer tous les commande precedent
        syntaxe_errors(line);
        free(line); // on free car readline il alloce 
    }
}

void printf_error(int x)
{
    if (x == 1)
    {
        write(2,"error input\n",13);
        write(2,"write 'minishell' ",19);
        exit(EXIT_FAILURE);
    }
    
}


int main(int ac, char **av)
{
    if (ac != 2)
        printf_error(1);
    else 
    {
        {
            if (ft_strcmp(av[1], "minishell") == 0)
                ft_read();
            else
                printf_error(1);
        }
    }
    return 0;
}

