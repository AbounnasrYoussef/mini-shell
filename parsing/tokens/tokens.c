/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:44:25 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/23 13:50:34 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


type_token get_token_type(char *str) {
    if (!strcmp(str, "|")) return PIPE;
    if (!strcmp(str, "<")) return RDR_IN;
    if (!strcmp(str, "<<")) return HERE_DOC;
    if (!strcmp(str, ">")) return RDR_OUT;
    if (!strcmp(str, ">>")) return APPEND;
    return WORD;
}


t_token *new_token(char *value, type_token type) {
    t_token *tok = malloc(sizeof(t_token));
    if (!tok) return NULL;
    tok->value = value;
    tok->type = type;
    tok->next = NULL;
    return tok;
}


void add_token(t_token **list, t_token *new_tok)
{
    if (!*list)
        *list = new_tok;
    else {
        t_token *tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_tok;
    }
}

void space_skip(char *line , int *i)
{
    while (line[*i] != '\0' && skip_space(line[*i]))
        (*i)++;
}

t_token *tokens(char *line)
{
    // char **cmd;
    t_token *tokens = NULL;
    // t_token cmd_tokens;
    int i = 0;
    int start  = 0;

    i = start;
    
    while (line[i] != '\0')
    {
        space_skip(line , &i);
        if (!line[i])
            break;
        if (is_quote(line[i]))
            handel_quote(line , &i , &tokens);
        else if (line[i] == '<' || line[i] == '>' || line[i + 1] == line[i])
            handel_double_operator(line , &i , &tokens);
        else if (is_operator(line[i]))
            handle_single_operator(line , &i , &tokens);
        else 
            handle_word(line, &i ,&tokens);
    } 
    for (t_token *t = tokens; t; t = t->next)
        printf("Token: %-12s | Type: %d\n", t->value, t->type);
    return tokens;
    
}
 

