/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 08:11:03 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/19 10:17:04 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void syntaxe_errors(char *args)
{
    int i = 0;
    while(args[i] != '\0')
    {
        if (args[i] == '|')
        {
            if (error_pipe(args , &i) == -1 )
                break;
        }
            
        else if (args[i] == '>' || args[i] == '<')
        {
            if (error_redir(args , &i)== -1 )
                break;
        }
        else if (args[i] == '\'' || args[i] == '\"')
        {
            if (error_quote(args) == -1)
                break;
        }
        i++; 
    }
}

