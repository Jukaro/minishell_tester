/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:21:20 by jfarkas           #+#    #+#             */
/*   Updated: 2023/04/22 18:56:50 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static long long	is_int(long long res, int negative)
{
	if (res >= 2147483648)
	{
		if (res > 2147483648 && negative == -1)
			return (0);
		else if (res >= 2147483648 && negative == 1)
			return (-1);
	}
	return (res);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	long long	res;
	int			negative;

	i = 0;
	res = 0;
	negative = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			negative *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		if (res > 2147483648)
			break ;
		i++;
	}
	res = is_int(res, negative);
	return ((int)(res * negative));
}
