/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:31:29 by mlaffita          #+#    #+#             */
/*   Updated: 2025/04/02 16:31:28 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char **line)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (NULL);
}

int	read_to_buffer(int fd, char *buffer)
{
	int	rd;

	rd = read(fd, buffer, BUFFER_SIZE);
	if (rd >= 0)
		buffer[rd] = '\0';
	return (rd);
}

int	update_line(char *buffer, char **line)
{
	char	*n_buff;

	n_buff = ft_strchr(buffer, '\n');
	if (n_buff)
	{
		*n_buff = '\0';
		*line = ft_strjoin_free(*line, buffer);
		if (!*line)
			return (0);
		*line = ft_strjoin_free(*line, "\n");
		if (!*line)
			return (0);
		ft_strlcpy(buffer, n_buff + 1, BUFFER_SIZE - (n_buff - buffer));
		return (1);
	}
	*line = ft_strjoin_free(*line, buffer);
	if (!*line)
		return (0);
	*buffer = '\0';
	return (0);
}

int	handle_end_of_file(int rd, char *buffer, char **line)
{
	if (rd == GNL_ERROR)
		return (0);
	if (rd == GNL_EOF && (!*line || **line == '\0') && buffer[0] == '\0')
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;
	int			rd;

	rd = 1;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer[0] == '\0')
		{
			rd = read_to_buffer(fd, buffer);
			if (!handle_end_of_file(rd, buffer, &line))
				return (ft_free(&line));
		}
		if (update_line(buffer, &line))
			return (line);
		if (rd == GNL_EOF)
			break ;
	}
	return (line);
}
