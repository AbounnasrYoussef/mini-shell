/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:22:31 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/26 15:16:24 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *expand_dollar(char *value, int *i, char **envp, int exit_code, garbage **garb)
{
    (*i)++;
    if (value[*i] == '?')
    {
        (*i)++;
        return ft_itoa(exit_code, garb);
    }

    int start = *i;
    while (ft_isalnum(value[*i]) || value[*i] == '_')
        (*i)++;
    
    char *var = ft_substr_gc(value, start, *i - start, garb);
    char *val = getenv_envp(var, envp); // à implémenter pour chercher dans envp
    return ft_strdup_gc(val ? val : "", garb);
}


char *expand_inside_double_quotes(char *value, int *i, char **envp, int exit_code, garbage **garb)
{
    int start = ++(*i);
    char *result = ft_strdup_gc("", garb);
    
    while (value[*i] && value[*i] != '"')
    {
        if (value[*i] == '$')
            result = ft_strjoin_gc(result, expand_dollar(value, i, envp, exit_code, garb), garb);
        else
        {
            char tmp[2] = { value[(*i)++], '\0' };
            result = ft_strjoin_gc(result, ft_strdup_gc(tmp, garb), garb);
        }
    }
    (*i)++; // skip closing "
    return result;
}

char *extract_single_quote(char *value, int *i, garbage **garb)
{
    int start = ++(*i);
    while (value[*i] && value[*i] != '\'')
        (*i)++;
    int len = *i - start;
    (*i)++; // Skip closing quote
    return ft_substr_gc(value, start - 1, len + 2, garb); // garde quotes
}


// hade fonction kta5ode chaine mn token o ktreturner  chaine jdida m3a ga3 les variables expandee
char *expand_token(char *value, int exit_code, char **envp, garbage **garb)
{
    // exit_code hiya valeur dial $? a utiliser
    // envp  tableau dial les variable d'environnement
    char *result ;
    int i = 0;

    result = ft_strdup("", garb); //hna fine knstokiwe version la5ra dial expand dial tokens
    while (value[i]) // mn hade ma wssalch ll la5er dial la chaine
    {
        if (value[i] == '\'') // ila l9ina quote gadi ijbed dakchi kamel hta lquote
            result = ft_strjoin(result, extract_single_quote(value, &i,garb), garb);
        else if (value[i] == '"') // quote double → expansion a l'interieur fl da5el
            result = ft_strjoin(result, expand_inside_double_quotes(value, &i, envp, exit_code, garb), garb);
        else if (value[i] == '$') // ila kane dollar gadi nexpandiwe.    
            result = ft_strjoin(result, expand_dollar(value, &i, envp, exit_code, garb), garb);
        else
        {
            char tmp[2] = { value[i++], '\0' };
            result = ft_strjoin(result, ft_strdup(tmp, garb), garb);
        }
    }

    return result;
}
