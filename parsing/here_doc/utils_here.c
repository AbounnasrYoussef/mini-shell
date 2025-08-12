/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:37:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/11 21:36:08 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_var_char_1(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	append_exit_status(char **tmp, t_garbage **garb)
{
	char	*status;

	status = ft_itoa(g_exit_status, garb);
	*tmp = ft_strjoin(*tmp, status, garb);
	return (1);
}

int	append_variable(char *line, t_list_env *env,
	t_garbage **garb, char **tmp)
{
	int		i;
	char	*name;
	char	*val;

	i = 0;
	while (is_valid_var_char_1(line[i]))
		i++;
	name = ft_substr(line, 0, i, garb);
	val = get_env_value(name, env, garb);
	*tmp = ft_strjoin(*tmp, val, garb);
	return (i);
}

int	append_raw_dollar(char **tmp, char c, t_garbage **garb)
{
	char	raw[3];

	raw[0] = '$';
	raw[1] = c;
	raw[2] = '\0';
	*tmp = ft_strjoin(*tmp, raw, garb);
	return (1);
}

int	append_normal_char(char **tmp, char c, t_garbage **garb)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	*tmp = ft_strjoin(*tmp, str, garb);
	return (1);
}
