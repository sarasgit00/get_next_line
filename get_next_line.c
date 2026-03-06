/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabo-gla <sabo-gla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:15:07 by sabo-gla          #+#    #+#             */
/*   Updated: 2025/11/07 18:15:08 by sabo-gla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *stash, char *buf)
{
	int		bytes;
	char	*temp;

	bytes = 1;
	while (bytes > 0 && !ft_strchr(stash, '\n'))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(stash);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		temp = ft_strjoin(stash, buf);
		if (!temp)
			return (NULL);
		stash = temp;
	}
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*newline_pos;
	int		line_len;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	newline_pos = ft_strchr(stash, '\n');
	if (newline_pos)
		line_len = newline_pos - stash + 1;
	else
		line_len = ft_strlen(stash);
	line = ft_substr(stash, 0, line_len);
	return (line);
}

static void	update_stash(char *stash, char *heap_stash)
{
	char	*newline_pos;
	size_t	i;
	size_t	j;

	if (!heap_stash)
		return ;
	newline_pos = ft_strchr(heap_stash, '\n');
	if (!newline_pos)
	{
		stash[0] = '\0';
		return ;
	}
	i = 0;
	j = (newline_pos - heap_stash) + 1;
	while (heap_stash[j] && i < BUFFER_SIZE)
	{
		stash[i] = heap_stash[j];
		i++;
		j++;
	}
	stash[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*buf;
	char		*heap_stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (stash[0] = '\0', NULL);
	heap_stash = ft_strdup(stash);
	if (!heap_stash)
		return (stash[0] = '\0', NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(heap_stash), stash[0] = '\0', NULL);
	heap_stash = read_to_stash(fd, heap_stash, buf);
	free(buf);
	if (!heap_stash)
		return (stash[0] = '\0', NULL);
	line = extract_line(heap_stash);
	if (line)
		update_stash(stash, heap_stash);
	else
		stash[0] = '\0';
	free(heap_stash);
	return (line);
}
