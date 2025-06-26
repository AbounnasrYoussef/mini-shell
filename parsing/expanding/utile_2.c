/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:27:14 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/26 08:27:47 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *getenv_envp(char *name, char **envp)
{
    int len = ft_strlen(name);
    for (int i = 0; envp[i]; i++)
    {
        if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
            return envp[i] + len + 1;
    }
    return NULL;
}