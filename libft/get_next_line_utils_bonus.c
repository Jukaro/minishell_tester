/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 04:51:06 by jfarkas           #+#    #+#             */
/*   Updated: 2022/11/11 13:44:28 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strlen_end(const char *str, char stop_count)
{
	int	size;

	size = 0;
	while (str[size] != '\0' && str[size] != stop_count)
		size++;
	return (size);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&((char *)s)[i]);
		i++;
	}
	if (s[i] == c)
		return (&((char *)s)[i]);
	return ((void *)0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)s = 0;
		s++;
		i++;
	}
}

size_t	gnl_ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	src_size;
	unsigned int	dest_size;
	int				i;
	int				j;

	if (size == 0)
		return (0);
	dest_size = ft_strlen_end(dest, '\0');
	src_size = ft_strlen_end(src, '\0');
	if (size <= dest_size)
		return (size + src_size);
	i = dest_size;
	j = 0;
	while (j < ((int)size - (int)dest_size - 1)
		&& (src[j] != '\0' && src[j] != '\n'))
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest_size + src_size);
}

void	update_buff(char *buff)
{
	unsigned int	i;
	unsigned int	size;
	char			*src;

	i = 0;
	size = ft_strlen_end(buff, '\0');
	if (size > 0)
	{
		src = ft_strchr(buff, '\n') + 1;
		while (i < size - 1 && src[i] != '\0')
		{
			buff[i] = src[i];
			i++;
		}
		while (i < size)
		{
			buff[i] = '\0';
			i++;
		}
	}
}
