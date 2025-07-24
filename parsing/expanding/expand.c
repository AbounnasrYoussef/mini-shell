/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/24 18:56:15 by yabounna         ###   ########.fr       */
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

// hade fonction hiya li kt7awel lina  token l texte $user =  youssef
char	*expand_token(char *value, int exit_code,t_list_env *env, garbage **garb)
{
    // value  hiya chaine original a anakyser
	int			i;
	char		*res; //hna fine gadi ndiro resultas final
	char		*tmp; // chaine teporaire bach nbniwe res
	t_expand_ctx	ctx;

	i = 0;
	res = ft_strdup("", garb);// hna bach ncommenciwe fwa7ed chaine valide han la chine 5awya 3ade gadi n3amroha bach maykoune ta segfault
	ctx.env = env;
	ctx.exit_code = exit_code;
	ctx.garb = garb;
	while (value[i]) // mn hade mawssalnach lla5er dial la chaine
	{
		if (value[i] == '\'') // ila kane simple quote 
			append_single_quote(value, &i, &res, garb); // gadi ncopiwe dakchili wassthom bl 7arf Entrée : 'Salut $USER' → Résultat : Salut $USER
		else if (value[i] == '"') // ilakano double quote
			append_double_quote(value, &i, &res, ctx);// hna 3awdo dollah bl value dialo Si USER=amine et entrée = "Salut $USER" → Résultat : Salut amine
		else if (value[i] == '$')
			res = ft_strjoin(res,expand_dollar(value, &i, exit_code, env, garb),garb);
		else
		{
			tmp = ft_substr(value, i, 1, garb);
			res = ft_strjoin(res, tmp, garb);
			i++;
		}
	}
	return (res);
}

void	expand_all_tokens(t_token **tokens, int exit_code,t_list_env *env, garbage **garb)
{
	t_token	*current;
	char	*expanded;
	t_token	*new_tokens;
	t_token	*last;
	t_token	*next;

	current = *tokens;
	while (current)
	{
		next = current->next;
		if (current->type == WORD && ft_strchr(current->value, '$'))
		{
			expanded = expand_token(current->value, exit_code, env, garb);
			if (!current->quoted)
			{
				new_tokens = split_into_tokens(expanded, garb);
				last = get_last_token(new_tokens);
				last->next = current->next;
				replace_token(tokens, current, new_tokens);
			}
			else
				current->value = expanded;
		}
		current = next;
	}
}



// void	expand_all_tokens(t_token *tokens, int exit_code,t_list_env *env, garbage **garb)
//                 // code de retour du dernier commande executer
// {
// 	char	*expanded;

// 	while (tokens) //tous les tokens
// 	{
// 		if (tokens->type == WORD && ft_strchr(tokens->value, '$')) // if ila kane token word o kayn fih dollar
// 		{
// 			expanded = expand_token(tokens->value, exit_code, env, garb);
// 			tokens->value = expanded;
// 		}
// 		tokens = tokens->next;
// 	}
// }

