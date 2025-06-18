/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:40:25 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/18 15:25:12 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void error_pipe(char *caracter , int i)
{
    int j = 0;
    
    if (i == 0)
        write(2 , " syntaxe error\n", 16);
    while (caracter[j] != '\0')
    {
        if (caracter[j] == '|' && caracter[j + 1] == '\0')
            write(2 , " syntaxe error\n", 16);
        j++;
    }
    
    
    
}
