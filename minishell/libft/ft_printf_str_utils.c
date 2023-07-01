/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:49:27 by jfarkas           #+#    #+#             */
/*   Updated: 2023/04/22 00:30:57 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	prtf_putchar(char ch, int *c)
{
	write(1, &ch, 1);
	(*c)++;
}

void	prtf_putstr(char *s, int *c)
{
	int	size;

	if (!s)
	{
		write(1, "(null)", 6);
		*c += 6;
		return ;
	}
	size = 0;
	while (s[size] != '\0')
	{
		(*c)++;
		size++;
	}
	write(1, s, size);
}
