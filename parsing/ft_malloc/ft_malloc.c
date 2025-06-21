/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:58:59 by yabounna          #+#    #+#             */
/*   Updated: 2025/06/21 12:06:21 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

garbage *ft_last(garbage *head)
{
    garbage *last;

    last = head;
    while (last->next)
        last = last->next;
    return (last);
}

// hade fonction kat allocer lina  w ktenregistrer dakchi li talloca f garbage collector
void *ft_malloc(garbage **garb , size_t size)
{
    void *ptr;

    ptr = malloc(size); // alloue la memoire demandee
    if (!ptr)
        return (ft_free_all(*garb), exit(EXIT_FAILURE), NULL);
    garbage *new = malloc(sizeof(garbage));
    // hna creena wa7ed noeud f dik la liste bach nenregistriwe  l'allocation
    if (!new) // hna ila dik allocation echouee 
    {
        ft_free_all(*garb);
        free(ptr);
        // perror
        exit(EXIT_FAILURE);
        return (NULL);
    }
    new->ptr = ptr ; // kn enregistriwe l'adresse dial allocation f ptr;
    if (*garb == NULL)
        *garb = new;
    else
        ft_last(*garb)->next = new; // knda5lo noeud fl bedia dial la list bach iweli new howa head;
    new->next = NULL;
    return ptr; // knretourniwe  dakchi li t alloca 
}

char *gc_strdup(garbage *garb , const char *s)
{
    if (!s) // la chaine n'est pas null
        return NULL;
    
    size_t len = ft_strlen(s) + 1; // kn7essbo la taille
    char *dup = ft_malloc(&garb , len); // allouer l amemoire avec garbage collector
    ft_memcpy(dup , s , len);
    return dup; // retourn la chaine dupliquer
}


// hna kn free toute la memoire allouer via le garbage collector
void ft_free_all(garbage *garb)
{
    garbage *current = garb;
    garbage *tmp; // bach nstokiwe le noeud liberer 

    while (current)
    {
        free(current->ptr); // libère la mémoire allouée.
        tmp = current;
        current = current->next;
        free(tmp);  // libère le conteneur du suivi.
    }
    garb = NULL; //on remet la liste à vide.
}

int main()
{
    garbage *head;

    head = NULL;
    char **str = ft_malloc(&head, 3 * 8);
    str[0] = strdup("fefefe");
    str[1] = strdup("fefef1e");
    str[2] = NULL;
    while (*str)
    {
        printf("%s\n",*str);
        str++;
    }
}
