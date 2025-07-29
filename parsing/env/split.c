/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:57:25 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/24 18:58:03 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
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

static char	**alloc(char const *s, char c)
{
	char	**sp;

	if (!s)
		return (NULL);
	sp = malloc(sizeof(char *) * (count_word(s, c) + 1));
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

char	**i_split(char const *s, char c)
{
	size_t	skip;
	size_t	i;
	size_t	index;
	size_t	sizee;
	char	**alloce_array;

	skip = 0;
	i = 0;
	index = 0;
	sizee = 0;
	alloce_array = alloc(s, c);
	if (!alloce_array)
		return (NULL);
	while (index < count_word(s, c))
	{
		sizee = count_len_word(s, c, &i, &skip);
		alloce_array[index] = (char *)malloc(sizeof(char) * (sizee + 1));
		if (!alloce_array[index])
			return (free_split(alloce_array, index));
		ft_memcpy(alloce_array[index], s + skip, sizee);
		alloce_array[index][sizee] = '\0';
		index++;
	}
	return (alloce_array[index] = NULL, alloce_array);
}
