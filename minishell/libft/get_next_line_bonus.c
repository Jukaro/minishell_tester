/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 04:51:04 by jfarkas           #+#    #+#             */
/*   Updated: 2023/05/07 20:11:51 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_strjoin_end(char const *line, char const *buff, char line_end)
{
	char	*join;
	int		line_s;
	int		buff_s;

	if (!line && !buff)
		return (NULL);
	line_s = ft_strlen_end(line, '\0');
	if (line_end == '\n')
		buff_s = ft_strlen_end(buff, '\n') + 2;
	else
		buff_s = ft_strlen_end(buff, '\0') + 1;
	join = malloc((line_s + buff_s) * sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_bzero(join, line_s + buff_s);
	gnl_ft_strlcat(join, line, line_s + 1);
	gnl_ft_strlcat(join, buff, line_s + buff_s);
	if (line_end == '\n')
		join[ft_strlen_end(join, '\0')] = '\n';
	free((char *)line);
	return (join);
}

void	get_next_buff(int fd, int *rd, char *buff)
{
	buff[BUFFER_SIZE] = '\0';
	ft_bzero(buff, ft_strlen_end(buff, '\0') + 1);
	*rd = read(fd, buff, BUFFER_SIZE);
}

char	*get_line(int fd, int *rd, char *buff)
{
	char	*line;

	line = malloc(sizeof(char));
	if (line == NULL)
		return (NULL);
	line[0] = '\0';
	while (!ft_strchr(buff, '\n'))
	{
		if (*rd == 0 && line[0] != '\0')
		{
			ft_bzero(buff, ft_strlen_end(buff, '\0') + 1);
			return (line);
		}
		else if (*rd <= 0)
		{
			free(line);
			return (NULL);
		}
		line = ft_strjoin_end(line, buff, '\0');
		if (line == NULL)
			return (NULL);
		get_next_buff(fd, rd, buff);
	}
	line = ft_strjoin_end(line, buff, '\n');
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			rd;
	static char	buff[MAX_FD][BUFFER_SIZE + 1] = {""};

	rd = 1;
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE == 0)
		return (NULL);
	line = get_line(fd, &rd, buff[fd]);
	if (line == NULL)
		return (NULL);
	update_buff(buff[fd]);
	return (line);
}
