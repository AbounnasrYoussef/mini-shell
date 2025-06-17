/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/17 12:59:27 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_read()
{
    char *input;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break; // if il y a un erreur 
        if (*input)
            add_history(input); // pour enregistrer tous les commande precedent
        free(input); // on free car readline il alloce 
    }
}

void printf_error()
{
    write(2,"error input\n",13);
    write(2,"write 'minishell' ",19);
    exit(EXIT_FAILURE);
}


int main(int ac, char **av)
{
    if (ac != 2)
        printf_error();
    else 
    {
        ft_read();
    }
    return 0;
}

