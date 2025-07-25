/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:34:51 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/25 12:19:38 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s1,garbage **garb)
{
	size_t	i;
	char	*d;

	i = ft_strlen(s1);
	d = (char *)ft_malloc(garb,((i + 1) * sizeof(char)));
	if (d == NULL)
		return (NULL);
	ft_memcpy(d, s1, i);
	d[i] = '\0';
	return (d);
}