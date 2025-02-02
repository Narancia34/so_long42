/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:09:37 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/28 15:39:10 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *remainder)
{
	int		i;
	char	*line;

	if (!remainder)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line = get_memcpy(line, remainder, i);
	line[i] = '\0';
	return (line);
}

char	*get_remainder(char *str)
{
	char	*p;
	char	*remainder;

	if (!str)
		return (NULL);
	p = get_strchr(str, '\n');
	if (!p)
		return (free(str), (NULL));
	remainder = get_strdup(p + 1);
	free (str);
	return (remainder);
}

char	*read_file(char *remainder, int fd)
{
	ssize_t		bytes_read;
	char		*buffer;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), (NULL));
		buffer[bytes_read] = '\0';
		remainder = get_strjoin(remainder, buffer);
		if (get_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	if (bytes_read == 0 && (!remainder || !*remainder))
		return (free(remainder), remainder = NULL);
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(remainder), NULL);
	if (!remainder)
		remainder = get_strdup("");
	if (!get_strchr(remainder, '\n'))
		remainder = read_file(remainder, fd);
	if (!remainder)
		return (free(remainder), NULL);
	line = get_line(remainder);
	remainder = get_remainder(remainder);
	return (line);
}
