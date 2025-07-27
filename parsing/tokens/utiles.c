/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:15:50 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/27 11:09:57 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*get_fused_word(const char *line, int *i, garbage **garb)
// {
// 	char	*res = ft_strdup("", garb);

// 	while (line[*i] && !skip_space(line[*i]) && !is_operator(line[*i]))
// 	{
// 		if (line[*i] == '\'')
// 			append_single_quote(line, i, &res, garb);
// 		else if (line[*i] == '"')
// 			append_double_quote(line, i, &res, garb);
// 		else
// 		{
// 			int start = *i;
// 			while (line[*i] && !skip_space(line[*i]) && !is_operator(line[*i])
// 				&& line[*i] != '\'' && line[*i] != '"')
// 				(*i)++;
// 			res = ft_strjoin(res,ft_substr(line, start, *i - start, garb), garb);
// 		}
// 	}
// 	return (res);
// }
