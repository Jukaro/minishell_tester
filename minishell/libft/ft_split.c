/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:18:12 by jfarkas           #+#    #+#             */
/*   Updated: 2022/09/27 21:18:14 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	wd_count;
	int	is_word;

	i = 0;
	wd_count = 0;
	is_word = 0;
	while (s[i])
	{
		if (s[i] != c && !is_word)
		{
			wd_count++;
			is_word = 1;
		}
		if (s[i] == c && is_word)
			is_word = 0;
		i++;
	}
	return (wd_count);
}

static void	free_split(char ***split, int wd_count)
{
	while (wd_count > 0)
	{
		free((*split)[wd_count] - 1);
		wd_count--;
	}
	free(*split);
	*split = NULL;
	return ;
}

static void	split_s(char ***split, char const *s, char c)
{
	int	wd_count;
	int	wd_size;
	int	i;

	i = 0;
	wd_count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			wd_size = 0;
			while (s[i + wd_size] != c && s[i + wd_size] != '\0')
				wd_size++;
			(*split)[wd_count] = ft_substr(s, i, wd_size);
			if ((*split)[wd_count] == NULL)
			{
				free_split(split, wd_count);
				return ;
			}
			i += wd_size - 1;
			wd_count++;
		}
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		wd_count;

	if (!s)
	{
		split = ft_calloc(1, sizeof(char *));
		return (split);
	}
	wd_count = count_words(s, c);
	if (wd_count == 0)
	{
		split = ft_calloc(1, sizeof(char *));
		return (split);
	}
	split = ft_calloc((wd_count + 1), sizeof(char *));
	if (split == NULL)
		return (NULL);
	split_s(&split, s, c);
	if (split == NULL)
		return (NULL);
	split[wd_count] = NULL;
	return (split);
}
