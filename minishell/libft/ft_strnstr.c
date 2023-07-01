/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:21:13 by jfarkas           #+#    #+#             */
/*   Updated: 2023/05/07 21:22:00 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_size;

	if (little[0] == 0)
		return ((char *)big);
	if (len == 0)
		return (0);
	little_size = ft_strlen(little);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len && j < little_size)
			j++;
		if (j == little_size)
			return (&((char *)big)[i]);
		i++;
	}
	return (NULL);
}
