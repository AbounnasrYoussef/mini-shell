/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 08:11:03 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/18 14:59:03 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void syntaxe_errors(char *args)
{
    int i = 0;
    while(args[i] != '\0')
    {
        if (args[i] == '|')
            error_pipe(args , i);
        // else if (args == '>' || args[i] == '<')
        //     syntaxe_errors_redi(args , i); 
        i++; 
    }
}

