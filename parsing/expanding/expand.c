/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 17:41:03 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void expand_all_tokens(t_token **tokens, int exit_code, t_list_env *env, garbage **garb)
{
	t_token *curr = *tokens;
	t_token *prev = NULL;

	while (curr)
	{
		char *expanded = expand_token(curr->value, exit_code, env, garb);
		char *cleaned = ft_strtrim_custom(expanded, garb, curr->quoted);
		if (!cleaned || cleaned[0] == '\0')
		{
			t_token *to_delete = curr;
			curr = curr->next;
			if (!prev)
				*tokens = to_delete->next;
			else
				prev->next = to_delete->next;
			continue;
		}
		curr->value = cleaned;

		prev = curr;
		curr = curr->next;
	}
}
