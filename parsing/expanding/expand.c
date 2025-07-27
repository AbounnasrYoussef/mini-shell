/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/27 12:40:01 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	add_token_back(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!head || !new_token)
		return ;
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

int ft_exit_status(int status, int flag)
{
	static int exit_status = 0;

	if (flag)
		exit_status = status;
	return (exit_status);
}
// hade fonction hiya li kt7awel lina  token l texte $user =  youssef
char	*expand_token(char *value, int exit_code, t_list_env *env, garbage **garb)
{
	int			i;
	char		*res;
	char		*tmp;
	t_expand_ctx	ctx;

	i = 0;
	ctx.env = env;
	ctx.exit_code = exit_code;
	ctx.garb = garb;
	res = ft_strdup("", garb);
	while (value[i])
	{
		if (value[i] == '\'')
			append_single_quote(value, &i, &res, garb);
		else if (value[i] == '"')
			append_double_quote(value, &i, &res, ctx);
		else if (value[i] == '$')
			res = ft_strjoin(res,
					expand_dollar(value, &i, exit_code, env, garb),
					garb);
		else
		{
			tmp = ft_substr(value, i, 1, garb);
			res = ft_strjoin(res, tmp, garb);
			i++;
		}
	}
	return (res);
}


void	expand_all_tokens(t_token **tokens, int exit_code, t_list_env *env, garbage **garb)
{
	t_token	*curr;
	t_token	*new_tokens;
	t_token	*last;
	char	*expanded;

	if (!tokens || !*tokens)
		return ;
	curr = *tokens;
	while (curr)
	{
		if (curr->type == WORD && ft_strchr(curr->value, '$'))
		{
			expanded = expand_token(curr->value, exit_code, env, garb);
			expanded = ft_strtrim_custom(expanded, garb, curr->quoted);
			if (!curr->quoted && ft_strchr(expanded, ' '))
			{
				new_tokens = split_into_tokens(expanded, garb);
				if (new_tokens)
				{
					replace_token(tokens, curr, new_tokens);
					last = new_tokens;
					while (last->next)
						last = last->next;
					curr = last;
				}
				else
					curr->value = expanded;
			}
			else
				curr->value = expanded;
		}
		curr = curr->next;
	}
}








