/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:22:31 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/24 13:20:21 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// Gère le cas d'une chaîne entre double quotes (quote "...") avec $ à interpréter
void	append_double_quote(const char *val, int *i, char **res,t_expand_ctx ctx)
{
	int		start;   // Début de la double quote
	char	*tmp;     // Pour extraire les caractères simples
	char	*part;    // Partie construite dans les quotes

	start = ++(*i);   // Passer la quote d'ouverture
	part = ft_strdup("", ctx.garb);  // Initialiser part vide
	while (val[*i] && val[*i] != '"')  // Lire jusqu'à la quote fermante
	{
		if (val[*i] == '$')  // Si on trouve un dollar
			part = ft_strjoin(part,expand_dollar((char *)val, i, ctx.exit_code, ctx.env, ctx.garb), ctx.garb);
			// On étend la variable avec sa valeur
		else
		{
			tmp = ft_substr(val, *i, 1, ctx.garb);
			// Extraire un caractère non-dollar
			part = ft_strjoin(part, tmp, ctx.garb);  // L'ajouter à part
			(*i)++;  // Passer au caractère suivant
		}
	}
	*res = ft_strjoin(*res, part, ctx.garb);  // Ajouter au résultat global
	(*i)++;  // Passer la quote fermante
}