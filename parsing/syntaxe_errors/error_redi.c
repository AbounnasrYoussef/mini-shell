/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:17:40 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/19 09:06:10 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int error_redir(char *caracter , int *i)
{
    (*i)++;
    while (caracter[*i] && skip_space(caracter[*i]))
        (*i)++;
    if (caracter[*i] == '|')
    {
        write(2, "minishell: syntax error\n", 25);
        return -1;
    }
        
    if (!caracter[*i] || caracter[*i] == '>' || caracter[*i] == '<')
    {
        write(2, "minishell: syntax error\n", 25);
        return -1;
    }
    return 1;
}
