/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:49:38 by jfarkas           #+#    #+#             */
/*   Updated: 2023/04/22 00:30:57 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	compute_arg(va_list ap, char arg_type, int *c)
{
	if (arg_type == 'c')
		prtf_putchar(va_arg(ap, int), c);
	else if (arg_type == 's')
		prtf_putstr(va_arg(ap, char *), c);
	else if (arg_type == 'i' || arg_type == 'd')
		prtf_putnbr(va_arg(ap, int), "0123456789", c);
	else if (arg_type == 'u')
		prtf_putunbr_base(va_arg(ap, unsigned int), "0123456789", c, 10);
	else if (arg_type == 'x')
		prtf_putunbr_base(va_arg(ap, unsigned int), "0123456789abcdef", c, 16);
	else if (arg_type == 'X')
		prtf_putunbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF", c, 16);
	else if (arg_type == 'p')
		prtf_putptr(va_arg(ap, unsigned long), c);
	else if (arg_type == '%')
		prtf_putchar('%', c);
	else
	{
		prtf_putchar('%', c);
		prtf_putchar(arg_type, c);
	}
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		c;
	va_list	ap;

	if (!str)
		return (-1);
	va_start(ap, str);
	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
			prtf_putchar(str[i], &c);
		else if (str[i + 1] != '\0')
		{
			compute_arg(ap, str[i + 1], &c);
			i++;
		}
		else
			c = -1;
		i++;
	}
	va_end(ap);
	return (c);
}
