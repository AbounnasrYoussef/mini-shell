/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/26 08:37:34 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void expand_all_tokens(t_token *tokens, int last_exit_code, char **envp, garbage **garb)
{
    while (tokens) // mn 7ade kaynine des tokens gadi tb9a la boucle 5edama
    {
        if (tokens->type == WORD && ft_strchr(tokens->value, '$'))
        {
            // kncheckiwe wach hadak token rah word o ila kane fih $
            char *expanded = expand_token(tokens->value, last_exit_code, envp, garb);
            // kn3ayto l expand_token hiya li ktraje3 lina chaine ola $var &? sont remplacer par leur valeur
            tokens->value = expanded; // On remplace l’ancien value du token par la version expandée.
        }
        tokens = tokens->next;
        // on passe a la token suivant fhadik la liste.
    }
}

