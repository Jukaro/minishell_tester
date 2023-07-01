/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:21:29 by jfarkas           #+#    #+#             */
/*   Updated: 2022/09/26 11:21:31 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	overflow_check;
	size_t	i;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(sizeof(char));
		return (ptr);
	}
	overflow_check = nmemb * size;
	if (overflow_check > INT_MAX || nmemb > INT_MAX || size > INT_MAX)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
