/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 08:11:03 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/18 10:53:09 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void syntaxe_errors(char *args)
{
    syntaxe_errors_pipe(args);
    syntaxe_errors_redi(args);

}

void syntaxe_errors_pipe(char *args)
{
    int i = 0;
    while (i <= ft_strlen(args))
    {
        while(args[i] == '\t' || args[i] ==' ')
            i++;
        if (args[0] == '|')
        {
            write(2,"   syntaxe error \n",19);
            break;
        }
        if ((args[i] == '|')&&  args[i + 1] == '\0')
        {
            write(2,"   syntaxe error \n",19);
        }
        i++;
    }
}
void syntaxe_errors_redi(char *args)
{
    int i = 0;


    while (i <= ft_strlen(args))
    {
        while(args[i] == '\t' || args[i] ==' ')
                i++;
                
        if ((args[0] == '>' || args[0] == '<') && (args[i+1] == '\0' ))
        {
            write(2,"   syntaxe error \n",19);
            break;
        }
        i++;    }
    
    
}
