/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:48:54 by jfarkas           #+#    #+#             */
/*   Updated: 2022/10/04 12:48:54 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		list_size;
	t_list	*ptr;

	list_size = 0;
	ptr = lst;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		list_size++;
	}
	return (list_size);
}
