/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigle_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:22:59 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/24 13:20:30 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

// Gère le cas d'une chaîne entre apostrophes simples (quote '...')
void	append_single_quote(const char *val, int *i, char **res,garbage **garb)
{
    // val hiya chine li gadi ntratiwe 
	int		start;  // Index du début de la chaîne entre quotes
	char	*tmp;    // Sous-chaîne à extraire

	start = ++(*i);  // Passer la quote d'ouverture et marquer le début
	while (val[*i] && val[*i] != '\'')  // Lire jusqu'à la quote fermante
		(*i)++;
	tmp = ft_substr(val, start - 1, *i - start + 2, garb);
	// Extraire toute la chaîne y compris les quotes
	*res = ft_strjoin(*res, tmp, garb);  // Ajouter au résultat
	(*i)++;  // Passer la quote fermante
}
