/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:30:32 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/27 09:12:57 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_word(const char *line, int *i, t_token **tokens , garbage **garb)
{
    int start = *i;// bedia dial mot li 7na fih db

    while (line[*i] && !skip_space(line[*i])
        && !is_operator(line[*i]) && !is_quote(line[*i]))
        (*i)++;  // loop htal la5er dial mot

    char *word = ft_substr(line, start, *i - start, garb);// Extrait le mot
    add_token(tokens, new_token(word, WORD,garb)); // cree token de type word et ajouter a la liste
}

// hna kngeriwe sigle operator | > <
void handle_single_operator(char *line, int *i, t_token **tokens , garbage **garb)
{
    char op[2] = {line[*i], '\0'};   
    add_token(tokens, new_token(ft_strdup(op, garb), get_token_type(op), garb));
    (*i)++;                         
}

// kn gerewe les operateur doublons >> << 
void handel_double_operator(char *line ,int *i , t_token **tokens, garbage **garb)
{
    char op[3] = {line[*i], line[*i + 1], '\0'};
    add_token(tokens, new_token(ft_strdup(op ,  garb), get_token_type(op), garb));
    
    *i += 2; // bach na9zo douk es caractere doublons
}
// hade fonction kt analyser un mot entre quotes
void handel_quote(char *line , int  *i , t_token **token ,garbage **garb)
{
    char quote ; // hna bach nstokiwe wach single ou double
    int start; // hadi position de debut dial contenu entre quote
    
    start = *i; // hna knenregistrer la position de depart
    quote =  line[(*i)++]; // knstokiwe quote o kndozo l caractere li wrah

    while (line[*i] && line[*i] != quote) // mn hade mawssalnach la5er dial quote gadi yb9a loop 5edama
    { // ola la fin dial chaine
        (*i)++; // navanciwe  hta nwasslo la5er
    }
    // hna kn5edmo f substr bach njebdo dakchi li waste lquotes
    (*i)++;
    char *quoted = ft_substr(line , start , *i - start , garb);
    add_token(token , new_token(quoted , WORD,garb));
    //kncrewe tokens jdida bdakchi li jbedna  b substr o type 
    
}