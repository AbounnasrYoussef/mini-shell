/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:44:25 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 11:50:08 by yabounna         ###   ########.fr       */
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
t_token	*new_token(char *value, type_token type,int i, garbage **garb)
{
	t_token	*tok;

	tok = ft_malloc(garb, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = ft_strdup(value, garb);
	tok->type = type;
    tok->join = 1;
	tok->quoted = i;
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

// t_token *tokens(char *line, garbage **garb)
// {
//     // char **cmd;
//     t_token *tokens = NULL;
//     // t_token cmd_tokens;
//     int i = 0;
    
//     while (line[i] != '\0') // knloopiwe 3la  chaque 
//     {
//         space_skip(line , &i); //ignorer les espaces 
//         if (!line[i]) // ki checker wach ba9a chi haja tanalysa
//             break;
//         if (is_quote(line[i])) // ila l9ina single ou double quote
//             handel_quote(line , &i , &tokens,garb);
//         else if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i])
//             handel_double_operator(line , &i , &tokens,garb);
//         else if (is_operator(line[i])) // ila kane chi operateur 
//             handle_single_operator(line , &i , &tokens,garb);
//         else  // ila  makane ta haja 9bel donc rah world
//             handle_word(line, &i ,&tokens,garb);
//     }
//     return tokens;
// }

t_token *tokens(char *line, garbage **garb)
{
    t_token *tokens = NULL;
    int i = 0;
    
    while (line[i] != '\0')
    {
        space_skip(line , &i);
        if (!line[i])
            break;
        if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i])
            handel_double_operator(line , &i , &tokens,garb);
        else if (is_operator(line[i]))
            handle_single_operator(line , &i , &tokens,garb);
        else
            handle_word(line, &i , &tokens,garb);  // <-- TOUJOURS ici, même pour les quotes
    }
    return tokens;
}

 

