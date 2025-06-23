/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:44:25 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/23 10:23:55 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void tokens(char *line)
{
    char **mot;
    // char **cmd;
    // t_token *tokens = NULL;
    // t_token cmd_tokens;
    int i = 0;
    mot = ft_split(line , '|');
    
    
    
    while (mot[i] != (void *)0 )
    {
        printf("%s\n", mot[i]);
        i++;
    } 
    
}
 

