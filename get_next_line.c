/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzima <lzima@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:56:23 by lzima             #+#    #+#             */
/*   Updated: 2022/01/11 11:27:27 by lzima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	see_the_matrix(char **statik, int fd)
{
	int		readed;
	char	buffer[BUFFER_SIZE + 1];
	int		enough;
	char	*your_mind;

	enough = 0;
	if (!*statik)
		*statik = ft_strdup("");
	while (!ft_strchr(*statik, '\n') && !enough)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		buffer[readed] = '\0';
		if (readed != BUFFER_SIZE)
			enough = 1;
		your_mind = *statik;
		*statik = ft_strjoin(*statik, buffer);
		free(your_mind);
	}
}

char	*the_one(char **statik)
{
	int		i;
	char	*neo_line;
	char	*your_mind;

	i = 0;
	while ((*statik)[i] != '\n' && (*statik)[i])
		i++;
	if ((*statik)[i] == '\n')
		i++;
	if (i == 0)
		return (NULL);
	neo_line = ft_substr(*statik, 0, i);
	your_mind = *statik;
	*statik = ft_substr(*statik, i, (ft_strlen(*statik) - i));
	free(your_mind);
	return (neo_line);
}

char	*get_next_line(int fd)
{
	static char	*statik;
	char		*neo_line;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	see_the_matrix(&statik, fd);
	neo_line = the_one(&statik);
	if (!neo_line)
	{
		free(neo_line);
		free(statik);
		statik = NULL;
		return (NULL);
	}
	return (neo_line);
}
