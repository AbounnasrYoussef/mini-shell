/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:58:57 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/29 15:38:26 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC
# define FT_MALLOC


#include "../../minishell.h"
#include <stdlib.h>
#include <string.h>

typedef struct garbage garbage;

garbage *ft_last(garbage *head);
void *ft_malloc(garbage **garb , size_t size);
void ft_free_all(garbage *garb);

#endif
