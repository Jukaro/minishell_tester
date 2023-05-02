/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:06:27 by jfarkas           #+#    #+#             */
/*   Updated: 2022/10/04 14:06:27 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*ptr;
	t_list	*new_elem;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new_list = NULL;
	ptr = lst;
	while (ptr != NULL)
	{
		new_elem = ft_lstnew(f(ptr->content));
		if (new_elem == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_elem);
		ptr = ptr->next;
	}
	return (new_list);
}
