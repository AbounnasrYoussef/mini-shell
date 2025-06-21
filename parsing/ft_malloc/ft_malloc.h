/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:58:57 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/21 11:57:17 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC
# define FT_MALLOC


#include "../minishell.h"
#include <stdlib.h>
#include <string.h>

typedef struct garbage
{
    void *ptr; // hada pointer generique vers n'importe quelle memoire allouee 
    struct garbage *next;  // hada next l prochaine element dial dik la list
}   garbage;


void *ft_malloc(garbage **garb , size_t size);
char *gc_strdup(garbage *garb , const char *s);
void ft_free_all(garbage *garb);

#endif
