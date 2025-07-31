/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:44:05 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 18:02:48 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_exec_list(t_exec *exec_list)
{
    t_exec *tmp;

    while (exec_list)
    {
        tmp = exec_list->next;

        // Libérer le tableau cmd
        if (exec_list->cmd)
        {
            int i = 0;
            while (exec_list->cmd[i])
            {
                free(exec_list->cmd[i]);
                i++;
            }
            free(exec_list->cmd);
        }

        // Libérer les fichiers (si ta structure t_file contient des pointeurs à libérer)
        // free_files(&exec_list->file); // à écrire selon ta structure t_file

        free(exec_list);
        exec_list = tmp;
    }
}