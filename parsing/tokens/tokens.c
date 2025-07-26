/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:44:25 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/26 10:49:24 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// hade fonction hiya li k determiner lina type dial token
type_token get_token_type(char *str) {
    if (!ft_strcmp(str, "|"))
        return PIPE;
    if (!ft_strcmp(str, "<"))
        return RDR_IN;
    if (!ft_strcmp(str, "<<"))
        return HERE_DOC;
    if (!ft_strcmp(str, ">"))
        return RDR_OUT;
    if (!ft_strcmp(str, ">>"))
        return APPEND;
    return WORD;
}

// kncrew wa7ed noeud
t_token	*new_token(char *value, type_token type, garbage **garb)
{
	t_token	*tok;

	tok = ft_malloc(garb, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = ft_strdup(value, garb);
	tok->type = type;
	tok->quoted = 0;
    tok->double_quote = 0;
	tok->next = NULL;
	return (tok);
}


// hade fontion bach nzido wa7ed token l la5er dial liste chainee 
void add_token(t_token **list, t_token *new_tok)
{// pointeur vers la tete et token jdid li gadi nzido
    if (!*list) // ila list kanet 5awya
        *list = new_tok; // kn assigniwe new_token la tete dial liste
    else { // ila list ga3ma 5awya
        t_token *tmp = *list;
        while (tmp->next) // knloppiwe hta knwasslo l'element la5er dial list
            tmp = tmp->next; 
        tmp->next = new_tok;// une fois kiwssal la5er ki zide new_token 
    }
}

void space_skip(char *line , int *i)
{
    while (line[*i] != '\0' && skip_space(line[*i]))
        (*i)++;
}



// hade lfonction  hiya li ktanalyser lina la line de commande

t_token *tokens(char *line, garbage **garb)
{
	t_token *tokens = NULL;
	int i = 0;

	while (line[i])
	{
		space_skip(line, &i);
		if (!line[i])
			break;
		if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i])
			handel_double_operator(line, &i, &tokens, garb);
		else if (is_operator(line[i]))
			handle_single_operator(line, &i, &tokens, garb);
		else
			handle_word(line, &i, &tokens, garb);
	}
	return tokens;
}

 

