/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lol.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:44:57 by jfarkas           #+#    #+#             */
/*   Updated: 2023/05/02 19:17:56 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void	segfault(void)
{
	char	*lol;

	lol = NULL;
	lol[9] = 'y';
	return ;
}

void	invalid_write(void)
{
	char	*lol;

	lol = malloc(8);
	lol[9] = 'y';
	free(lol);
	return ;
}

int main()
{
	char	*str;

	str = NULL;
	while (ft_strncmp(str, "exit", 5))
	{
		str = readline("minishell : ");
		if (!ft_strncmp(str, "segfault", 9))
			segfault();
		if (!ft_strncmp(str, "invalid write", 14))
			invalid_write();
		printf("resultat de %s\n", str);
		//fflush(stdout);
	}
	return (0);
}
