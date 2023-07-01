/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:19:21 by jfarkas           #+#    #+#             */
/*   Updated: 2022/09/27 21:19:22 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	int	size;

	if (s == 0)
	{
		write(fd, "\n", 1);
		return ;
	}
	size = 0;
	while (s[size] != '\0')
		size++;
	write(fd, s, size);
	write(fd, "\n", 1);
}
