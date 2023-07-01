/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lol.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:44:57 by jfarkas           #+#    #+#             */
/*   Updated: 2023/05/08 01:24:56 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <string.h>
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

void	long_answer(void)
{
	printf("mdr\nmdr\nmdr\nmdr\n");
}

int main()
{
	char	*str;

	str = NULL;
	while (ft_strncmp(str, "exit", 5))
	{
		str = readline("minishell : ");
		if (!strcmp(str, "segfault"))
			segfault();
		if (!strcmp(str, "invalid write"))
			invalid_write();
		if (!strcmp(str, "long answer"))
			long_answer();
		if (strcmp(str, "no answer"))
			printf("resultat de %s\n", str);
	}
	return (0);
}
