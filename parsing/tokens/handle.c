/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:30:32 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/23 13:49:46 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_word(const char *line, int *i, t_token **tokens)
{
    int start = *i;                                // Début du mot

    while (line[*i] && !skip_space(line[*i])
        && !is_operator(line[*i]) && !is_quote(line[*i]))
        (*i)++;                                    // Avance jusqu’à fin du mot

    char *word = ft_substr(line, start, *i - start);   // Extrait le mot
    add_token(tokens, new_token(word, WORD));     // Ajoute comme WORD
}
void handle_single_operator(char *line, int *i, t_token **tokens) {
    char op[2] = {line[*i], '\0'};   
    add_token(tokens, new_token(strdup(op), get_token_type(op)));
    (*i)++;                         
}


void handel_double_operator(char *line ,int *i , t_token **tokens)
{
    char op[3] = {line[*i], line[*i + 1], '\0'};
    add_token(tokens, new_token(ft_strdup(op), get_token_type(op)));
    *i += 2; 
}
void handel_quote(char *line , int  *i , t_token **token)
{
    char quote ;
    int start;
    
    quote =  line[(*i)++];
    start = *i;

    while (line[*i] && line[*i] != quote)
    {
        (*i)++;
    }
    if (!line[*i])
    {
        perror("Syntaxe error : unclodes quote\n");
        exit(1);
    }
    char *quoted = ft_substr(line , start , *i-start);
    add_token(token , new_token(quoted , WORD));
    (*i)++;
    
}