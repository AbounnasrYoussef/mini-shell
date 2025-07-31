/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:55 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 18:18:49 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	append_single_quote(const char *val, int *i
		, char **res, t_garbage **garb)
{
	int		start;
	char	*tmp;

	start = ++(*i);
	while (val[*i] && val[*i] != '\'')
		(*i)++;
	tmp = ft_substr(val, start, *i - start, garb);
	*res = ft_strjoin(*res, tmp, garb);
	if (val[*i] == '\'')
		(*i)++;
}
