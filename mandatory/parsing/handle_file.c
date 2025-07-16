/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:17:47 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/14 17:17:49 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	check_file_type(char *path, char *format)
{
	int	len;

	len = 0;
	len = ft_strlen(path);
	if (len >= 4)
	{
		if (ft_strcmp(&path[len - 4], format) == 0)
			return (true);
	}
	ft_printf_fd(2, FILE_FORM, format);
	return (false);
}

bool	safe_open(char *path, int *fd)
{
	int		temp;
	char	t[1];
	ssize_t	tn;

	temp = 0;
	temp = open(path, O_RDONLY);
	if (temp < 0)
		return (perror(FILE_OPEN), false);
	tn = read(temp, t, 1);
	if (tn == -1)
		return (perror(FILE_READ), close(temp), false);
	if (tn == 0)
		return (ft_printf_fd(2, FILE_EMPTY), close(temp), false);
	close(temp);
	*fd = open(path, O_RDONLY);
	return (true);
}

char	**add_line(char *line, char **mat)
{
	int		len;
	char	**r;
	int		i;

	len = 0;
	i = 0;
	r = NULL;
	if (mat)
		len = ft_matlen(mat);
	r = malloc((len + 2) * sizeof(char *));
	if (!r)
		return (ft_printf_fd(2, E_ALLOC)
			, ft_freemat((void **)mat, ft_matlen(mat)), NULL);
	while (mat && mat[i])
	{
		r[i] = mat[i];
		i++;
	}
	if (mat)
		free(mat);
	r[i] = line;
	r[i + 1] = NULL;
	return (r);
}

char	**read_file(char *path)
{
	int		fd;
	char	**r;
	char	*line;

	fd = 0;
	r = NULL;
	line = NULL;
	if (!check_file_type(path, ".cub"))
		return (NULL);
	if (!safe_open(path, &fd))
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		r = add_line(line, r);
		if (r == NULL)
			return (free(line), close(fd), NULL);
		line = get_next_line(fd);
	}
	close(fd);
	return (r);
}
