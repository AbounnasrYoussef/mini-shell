/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:58:57 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 14:25:12 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "../../minishell.h"
# include <stdlib.h>
# include <string.h>

typedef struct s_garbage	t_garbage;

t_garbage	*ft_last(t_garbage *head);
void		*ft_malloc(t_garbage **garb, size_t size);
void		ft_free_all(t_garbage *garb);

#endif
