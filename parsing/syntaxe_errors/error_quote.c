/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:08:48 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/19 09:37:02 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int error_quote(char *caracter)
{
    char quote;
    int i = 0;
    while (caracter[i] != '\0')
    {
        if (caracter[i] == '\'' || caracter[i] == '\"')
        {
            quote = caracter[i++];
            while (caracter[i] != '\0' && caracter[i] != quote)
                i++;
            if (!caracter[i])
            {
                write(2, "minishell: syntax error\n", 25);
                return -1;
            }
        }
        i++;
    }
    return 1;
}