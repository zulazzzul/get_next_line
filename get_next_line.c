/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-abreu <nd-abreu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 21:01:31 by nd-abreu          #+#    #+#             */
/*   Updated: 2026/06/18 20:29:39 by nd-abreu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void *ft_clean(char **storage_box)
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
		buffer = malloc ((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return(ft_clean(storage_box));
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
