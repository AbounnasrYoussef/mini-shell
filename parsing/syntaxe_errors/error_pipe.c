/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:59:42 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/24 21:05:49 by yabounna         ###   ########.fr       */
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