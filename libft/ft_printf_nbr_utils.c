/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:50:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/04/22 00:30:57 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	prtf_putnbr(int n, char *base, int *c)
{
	if (n == -2147483648)
		prtf_putstr("-2147483648", c);
	else if (n < 0)
	{
		n *= -1;
		prtf_putchar('-', c);
	}
	if (n >= 10)
	{
		prtf_putnbr(n / 10, base, c);
		prtf_putnbr(n % 10, base, c);
	}
	if (n >= 0 && n < 10)
		prtf_putchar(base[n], c);
}

void	prtf_putunbr_base(unsigned int nbr, char *base, int *c, int base_s)
{
	if (nbr >= (unsigned int)base_s)
	{
		prtf_putunbr_base(nbr / base_s, base, c, base_s);
		prtf_putunbr_base(nbr % base_s, base, c, base_s);
	}
	if (nbr < (unsigned int)base_s)
		prtf_putchar(base[nbr], c);
}

void	prtf_putlnbr_hex(unsigned long nbr, char *base, int *c)
{
	if (nbr >= 16)
	{
		prtf_putlnbr_hex(nbr / 16, base, c);
		prtf_putlnbr_hex(nbr % 16, base, c);
	}
	if (nbr < 16)
		prtf_putchar(base[nbr], c);
}

void	prtf_putptr(unsigned long nb, int *c)
{
	if (!nb)
		prtf_putstr("(nil)", c);
	else
	{
		prtf_putstr("0x", c);
		prtf_putlnbr_hex(nb, "0123456789abcdef", c);
	}
}
