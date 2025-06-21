/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:40:25 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/20 13:04:12 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int error_pipe(char *caracter , int *i)
{
    (*i)++;
    if(caracter[0] == '|')
    {
        write(2, "minishell: syntax error\n", 25);
        return -1;
    }
    while(caracter[*i] && skip_space(caracter[*i]))
        (*i)++;
    if (!caracter[*i] || caracter[*i] == '|' || caracter[*i] == '<' || caracter[*i] == '>')
    {
        write(2, "minishell: syntax error\n", 25);
        return -1;
    }
    return 1;
    
}
