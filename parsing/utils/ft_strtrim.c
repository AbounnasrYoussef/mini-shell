/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 08:41:47 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 15:53:37 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static short	find_world(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set, garbage **garb)
{
	size_t	debut;
	size_t	fin;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup("", garb));  // ✅ Déjà gérée avec garbage

	debut = 0;
	fin = ft_strlen(s1) - 1;

	while (s1[debut] && find_world(s1[debut], set))
		debut++;
	while (fin > debut && find_world(s1[fin], set))
		fin--;

	len = fin - debut + 1;
	return (ft_substr(s1, debut, len, garb));  // ✅ Appel direct
}

