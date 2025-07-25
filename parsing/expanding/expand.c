/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/25 14:17:18 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	expand_all_tokens(t_token *tokens, int exit_code,t_list_env *env, garbage **garb)
                // code de retour du dernier commande executer
{
	char	*expanded;

	while (tokens) //tous les tokens
	{
		if (tokens->type == WORD && ft_strchr(tokens->value, '$')) // if ila kane token word o kayn fih dollar
		{
			expanded = expand_token(tokens->value, exit_code, env, garb);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}

