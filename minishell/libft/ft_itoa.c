/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:18:20 by jfarkas           #+#    #+#             */
/*   Updated: 2022/09/27 21:18:23 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_negative(int *n, int *negative, long *n_long, int *n_size)
{
	if (*n < 0)
	{
		*negative = 1;
		*n_long *= -1;
		*n_size += 1;
	}
}

static void	set_size(long *n_copy, int *n_size)
{
	while (*n_copy >= 10)
	{
		*n_copy /= 10;
		*n_size += 1;
	}
}

static char	*write_nb_str(char *nb_str, long *n_long, int *n_size)
{
	int		i;

	i = 0;
	while (*n_long >= 10)
	{
		nb_str[*n_size - 1] = *n_long % 10 + '0';
		*n_long /= 10;
		(*n_size)--;
		i++;
	}
	nb_str[*n_size - 1] = *n_long % 10 + '0';
	return (nb_str);
}

char	*ft_itoa(int n)
{
	char	*nb_str;
	int		negative;
	long	n_copy;
	long	n_long;
	int		n_size;

	n_size = 1;
	n_long = (long)n;
	negative = 0;
	set_negative(&n, &negative, &n_long, &n_size);
	n_copy = n_long;
	set_size(&n_copy, &n_size);
	nb_str = ft_calloc((n_size + 1), sizeof(char));
	if (nb_str == NULL)
		return (NULL);
	if (negative == 1)
		nb_str[0] = '-';
	nb_str = write_nb_str(nb_str, &n_long, &n_size);
	return (nb_str);
}
