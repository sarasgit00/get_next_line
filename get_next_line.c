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

/*
#include "get_next_line.h"
char    *get_next_line(int fd)
{
    char        *buffer;
    static char *stash;
    int         bytes_read;
    char        *newline_pos;
    int         newline_index;
    char        *line;
    char        *temp;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    bytes_read = 1;
    while (bytes_read > 0 && !ft_strchr(stash, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buffer);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        stash = ft_strjoin(stash, buffer);
    }
    if (stash == NULL || stash[0] == '\0')
    {
        free(buffer);
        return (NULL);
    }
    newline_pos = ft_strchr(stash, '\n');
    if (newline_pos != NULL)
        newline_index = newline_pos - stash;
    else
        newline_index = -1;
    line = ft_substr(stash, 0, (newline_index + 1));
    temp = ft_strdup(stash + newline_index + 1);
    free(stash);
    stash = temp;
    free(buffer);
    return line;
}
*/

#include "get_next_line.h"

static char *readn_stash(char *stash, int fd)
{
    char *buff;
    int bytes_read_buff;

    buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (buff == NULL)
        return(NULL);
    bytes_read_buff = 1;    
    while (bytes_read_buff > 0 && !ft_strchr(stash, '\n'))
    {
        bytes_read_buff = read(fd, buff, BUFFER_SIZE);
        if (bytes_read_buff == -1)
        {
            free(buff);
            if(stash)
                free(stash);
            return(NULL);
        }
        buff[bytes_read_buff] = '\0';
        stash = ft_strjoin(stash, buff);
    }
    free(buff);
    return(stash);
}

static char *lines(char *stash)
{
    char    *newline_start;
    int     newline_index;
    char    *line;

    if (stash == NULL || stash[0] == '\0')
        return (NULL);
    
    newline_start = ft_strchr(stash, '\n');
    if (newline_start)
        newline_index = newline_start - stash;
    else
        newline_index = -1;

    if (newline_index >= 0)
        line = ft_substr(stash, 0, newline_index + 1);
    else
        line = ft_strdup(stash);
    // if(!line)
    //     return(NULL);

    return (line);
}

static char *delete_used_stash(char *stash)
{
    char    *newline_start;
    int     newline_index;
    char    *updated_stash;

    newline_start = ft_strchr(stash, '\n');
    if (newline_start != NULL)
        newline_index = newline_start - stash;
    else
        newline_index = -1;

    if (newline_index == -1)
    {
        free(stash);
        return (NULL);
    }

    updated_stash = ft_substr(stash, newline_index + 1, ft_strlen(stash) - (newline_index + 1));
    free(stash);

    return (updated_stash);
}

char *get_next_line(int fd)
{
    static char *stash;
    char *line;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    stash = readn_stash(stash, fd);
    if(!stash || stash[0] == '\0')
    {
        free(stash);
        stash = NULL;
        return (NULL);
    }
    line = lines(stash);
    stash = delete_used_stash(stash);
    return (line);
}
