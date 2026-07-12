/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-abreu <nd-abreu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 23:00:30 by nd-abreu          #+#    #+#             */
/*   Updated: 2026/06/27 23:01:26 by nd-abreu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 

#include "get_next_line_bonus.h"

static void	*ft_clean(char **storage_box)
{
	free(*storage_box);
	*storage_box = NULL;
	return (NULL);
}

char	*ft_search_newline(int fd, char **storage_box)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	while ((bytes_read > 0) && (!ft_strchr(*storage_box, '\n')))
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (ft_clean(storage_box));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (ft_clean(storage_box));
		}
		buffer[bytes_read] = '\0';
		temp = *storage_box;
		*storage_box = ft_strjoin(*storage_box, buffer);
		free(temp);
		free(buffer);
	}
	return (*storage_box);
}

char	*get_next_line(int fd)
{
	static char	*storage_box[MAX_FD];
	char		*to_print;
	char		*temp;
	int			newline_pos;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	ft_search_newline(fd, &storage_box[fd]);
	if (!storage_box[fd] || !*storage_box[fd])
		return (free(storage_box[fd]), storage_box[fd] = NULL, NULL);
	if (!ft_strchr(storage_box[fd], '\n'))
		newline_pos = ft_strlen(storage_box[fd]);
	else
		newline_pos = (ft_strchr(storage_box[fd], '\n') - storage_box[fd] + 1);
	to_print = ft_substr(storage_box[fd], 0, newline_pos);
	if (!to_print)
		return (ft_clean(&storage_box[fd]));
	temp = storage_box[fd];
	storage_box[fd] = ft_substr(storage_box[fd], newline_pos,
			ft_strlen(storage_box[fd]) - newline_pos);
	free(temp);
	return (to_print);
}
