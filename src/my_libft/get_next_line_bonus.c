/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:48:05 by lmenoni           #+#    #+#             */
/*   Updated: 2025/01/07 16:48:07 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_next(char *archive)
{
	char	*r;
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (archive[i] && archive[i] != '\n')
		i++;
	if (archive[i] == '\n')
		i++;
	if (archive[i] == '\0')
		return (free(archive), NULL);
	r = malloc((ft_bufflen(archive) - i + 1) * sizeof(char));
	if (!r)
		return (free(archive), NULL);
	while (archive[i] != '\0')
		r[j++] = archive[i++];
	free(archive);
	r[j] = '\0';
	return (r);
}

char	*ft_get_line(char *archive)
{
	char	*r;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (archive[len] && archive[len] != '\n')
		len++;
	if (archive[len] == '\n')
		len++;
	r = malloc((len + 1) * sizeof(char));
	if (!r)
		return (NULL);
	while (r && i < len)
	{
		r[i] = archive[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_read_file(char *archive, int fd)
{
	char	*buffer;
	int		bytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(archive), NULL);
	bytes = 1;
	while (!ft_find(archive, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), free(archive), NULL);
		buffer[bytes] = '\0';
		archive = ft_buffjoin(archive, buffer);
	}
	free(buffer);
	if (bytes == 0 && (!archive || archive[0] == '\0'))
		return (free(archive), NULL);
	return (archive);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*archive[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	archive[fd] = ft_read_file(archive[fd], fd);
	if (!archive[fd])
		return (NULL);
	line = ft_get_line(archive[fd]);
	archive[fd] = ft_get_next(archive[fd]);
	return (line);
}
