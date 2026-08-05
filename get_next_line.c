/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-abreu <nd-abreu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 20:12:41 by nd-abreu          #+#    #+#             */
/*   Updated: 2026/07/30 01:39:11 by nd-abreu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_remainder(char *remainder)
{
	char	*newline;
	char	*new_remainder;

	newline = ft_strchr(remainder, '\n');
	if (!newline || newline[1] == '\0')
	{
		free(remainder);
		return (NULL);
	}
	new_remainder = ft_strdup(newline + 1);
	free(remainder);
	return (new_remainder);
}

char	*extract_line(char *remainder)
{
	char	*newline;
	size_t	len;

	if (!remainder)
		return (NULL);
	newline = ft_strchr(remainder, '\n');
	if (newline)
		len = (size_t)(newline - remainder) + 1;
	else
		len = ft_strlen(remainder);
	return (ft_substr(remainder, 0, len));
}

char	*read_loop(int fd, char *remainder, char *buf)
{
	char	*tmp;
	ssize_t	bytes_read;

	while (!ft_strchr(remainder, '\n'))
	{
		bytes_read = read(fd, buf, (size_t)BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(remainder);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		tmp = ft_strjoin(remainder, buf);
		free(remainder);
		remainder = tmp;
		if (!remainder)
			return (NULL);
	}
	return (remainder);
}

char	*read_until_newline(int fd, char *remainder)
{
	char	*buf;

	if (!remainder)
	{
		remainder = ft_strdup("");
		if (!remainder)
			return (NULL);
	}
	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
	{
		free(remainder);
		return (NULL);
	}
	remainder = read_loop(fd, remainder, buf);
	free(buf);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = read_until_newline(fd, remainder);
	if (!remainder || remainder[0] == '\0')
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	line = extract_line(remainder);
	remainder = update_remainder(remainder);
	if (!line)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	return (line);
}
