/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:18:05 by jfarkas           #+#    #+#             */
/*   Updated: 2022/10/03 16:04:59 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_beginning(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (!ft_strchr(set, s1[i]))
			break ;
		else
			i++;
	}
	return (i);
}

static size_t	count_end(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		if (!ft_strchr(set, s1[i]))
			break ;
		else
			i--;
	}
	i = ft_strlen(s1) - i - 1;
	return ((size_t)i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	begin_c;
	size_t	end_c;

	if (!s1 || !set)
		return (NULL);
	begin_c = count_beginning(s1, set);
	end_c = count_end(s1, set);
	if (begin_c == ft_strlen(s1))
	{
		trim = ft_calloc(1, sizeof(char));
		return (trim);
	}
	trim = ft_calloc((ft_strlen(s1) - begin_c - end_c + 1), sizeof(char));
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, s1 + begin_c, ft_strlen(s1) - begin_c - end_c + 1);
	return (trim);
}
