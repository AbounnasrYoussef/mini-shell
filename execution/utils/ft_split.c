/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:53:52 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/03 19:40:36 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static size_t	count_word(char const *s, char c)
{
	size_t	len;
	size_t	count;

	len = 0;
	count = 0;
	while (s[len])
	{
		while (s[len] == c)
			len++;
		while (s[len])
		{
			if (s[len] == c || s[len + 1] == '\0')
			{
				count++;
				break ;
			}
			len++;
		}
		if (s[len] == '\0')
			break ;
		len++;
	}
	return (count);
}

static int	count_len_word(char const *s, char c, size_t *j, size_t *skip)
{
	size_t	longueur;

	longueur = 0;
	while (s[*j] == c)
		(*j)++;
	*skip = *j;
	while (s[*j])
	{
		if (s[*j] != c)
			longueur++;
		else
			break ;
		(*j)++;
	}
	return (longueur);
}

static char	**alloc(char const *s, char c, t_garbage **garb)
{
	char	**sp;

	(void)garb;
	if (!s)
		return (NULL);
	sp = ft_malloc(garb, sizeof(char *) * (count_word(s, c) + 1));
	if (!sp)
		return (NULL);
	return (sp);
}

static void	*free_split(char **array, int i)
{
	while (--i >= 0)
		free(array[i]);
	free(array);
	return (NULL);
}

char	**ft_splitt(char const *s, char c, t_garbage **garb)
{
	size_t	skip;
	size_t	i;
	size_t	index;
	size_t	sizee;
	char	**alloce_array;

	(void)garb;
	skip = 0;
	i = 0;
	index = 0;
	sizee = 0;
	alloce_array = alloc(s, c, garb);
	if (!alloce_array)
		return (NULL);
	while (index < count_word(s, c))
	{
		sizee = count_len_word(s, c, &i, &skip);
		alloce_array[index] = (char *)ft_malloc(garb, sizeof(char) * (sizee + 1));
		if (!alloce_array[index])
			return (free_split(alloce_array, index));
		ft_memcpyy(alloce_array[index], s + skip, sizee);
		alloce_array[index][sizee] = '\0';
		index++;
	}
	return (alloce_array[index] = NULL, alloce_array);
}
