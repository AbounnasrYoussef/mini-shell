/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:30:32 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/24 14:44:45 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_word(const char *line, int *i, t_token **tokens , garbage **garb)
{
    int start = *i;                                // Début du mot

    while (line[*i] && !skip_space(line[*i])
        && !is_operator(line[*i]) && !is_quote(line[*i]))
        (*i)++;                                    // Avance jusqu’à fin du mot

    char *word = ft_substr(line, start, *i - start);   // Extrait le mot
    add_token(tokens, new_token(word, WORD,garb));     // Ajoute comme WORD
}
void handle_single_operator(char *line, int *i, t_token **tokens , garbage **garb)
{
    char op[2] = {line[*i], '\0'};   
    add_token(tokens, new_token(ft_strdup(op), get_token_type(op), garb));
    (*i)++;                         
}


void handel_double_operator(char *line ,int *i , t_token **tokens, garbage **garb)
{
    char op[3] = {line[*i], line[*i + 1], '\0'};
    add_token(tokens, new_token(ft_strdup(op), get_token_type(op), garb));
    *i += 2; 
}


// hade fonction kt analyser un mot entre quotes
void handel_quote(char *line , int  *i , t_token **token ,garbage **garb)
{
    char quote ; // hna bach nstokiwe wach single ou double
    int start; // hadi position de debut dial contenu entre quote
    
    quote =  line[(*i)++]; // knstokiwe quote o kndozo l caractere li wrah
    start = *i; // hna knenregistrer la position de depart

    while (line[*i] && line[*i] != quote) // mn hade mawssalnach la5er dial quote gadi yb9a loop 5edama
    { // ola la fin dial chaine
        (*i)++; // navanciwe  hta nwasslo la5er
    }
    char *quoted = ft_substr(line , start , *i-start);
    // hna kn5edmo f substr bach njebdo dakchi li waste lquotes
    add_token(token , new_token(quoted , WORD,garb));
    //kncrewe tokens jdida bdakchi li jbedna  b substr o type 
    (*i)++; // kndepassiwe sedda dial quote bach nkemlo tokenization
    
}