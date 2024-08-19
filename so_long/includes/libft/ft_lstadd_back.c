/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:03:16 by adiler            #+#    #+#             */
/*   Updated: 2024/08/19 19:25:23 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *last;

    printf("Debug: Entering ft_lstadd_back\n");
    if (lst == NULL || new == NULL)
    {
        printf("Debug: lst or new is NULL in ft_lstadd_back\n");
        return;
    }
    if (*lst == NULL)
    {
        *lst = new;
        printf("Debug: Added first node to empty list\n");
    }
    else
    {
        last = ft_lstlast(*lst);
        last->next = new;
        printf("Debug: Added node to end of list\n");
    }
}
