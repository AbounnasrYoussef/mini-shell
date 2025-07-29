/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:34:18 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/25 11:37:00 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') || (c == '_'));
}

char	*ft_strtrim_custom(char *str, garbage **garb, int quoted)
{
	if (quoted)
		return (str);
	return (ft_strtrim(str, " \t", garb));
}