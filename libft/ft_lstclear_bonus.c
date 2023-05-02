/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:25:46 by jfarkas           #+#    #+#             */
/*   Updated: 2022/10/04 13:25:46 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*before_elem;

	if (del == NULL || lst == NULL)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		del(ptr->content);
		before_elem = ptr;
		ptr = ptr->next;
		free(before_elem);
	}
	*lst = NULL;
}
