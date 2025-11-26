/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabo-gla <sabo-gla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 19:22:13 by sabo-gla          #+#    #+#             */
/*   Updated: 2025/11/11 00:08:43 by sabo-gla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t  index;

	if(!str)
		return(0);
	index = 0;
	while (str[index] != '\0')
	{
		index++;
	}
	return (index);
}

char	*ft_strchr(const char *s, int c)
{
	size_t  index;

	if (s == NULL)
		return (NULL);
	index = 0;
	while (s[index])
	{
		if (s[index] == (char)c)
			return ((char *)(s + index));
		index++;
	}
	return (NULL);
}

// char    *ft_strjoin(char *s1, char *s2)
// {
//     size_t  s1_len;
//     size_t  s2_len;
//     char    *new_str;

//     if(s1 == NULL && s2 == NULL)
//         return(NULL);
//     if (!s1)
//         return (ft_strdup(s2));
//     if (!s2)
//         return (ft_strdup(s1));
//     s1_len = ft_strlen(s1);
//     s2_len = ft_strlen(s2);
//     new_str = malloc(sizeof(char) * (s2_len+ s1_len + 1));
//     if (new_str == NULL)
//         return (NULL);
//     help_strjoin(new_str, s1, s2);
//     return(new_str);
// }

// void help_strjoin(char *dest, char *s1, char *s2)
// {
//     unsigned int i;
//     unsigned int k;

//     i = 0;
//     k = 0;
//     while(s1[i])
//         dest[k++] = s1[i++];
//     i  = 0;
//     while (s2[i])
//         dest[k++] = s2[i++];
//     dest[k] = '\0';
// }

char    *ft_strjoin(char *s1, char *s2)
{
	char    *new;
	size_t  i;
	size_t  j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}


char    *ft_strdup(const char *s)
{
	size_t  index;
	char    *ptr_to_dst;

	if (!s)
		return (NULL);
	index = 0;
	while (s[index])
		index++;
	ptr_to_dst = (char *)malloc(sizeof(char) * (index + 1));
	if (ptr_to_dst == NULL)
		return (NULL);
	index = 0;
	while (s[index])
	{
		ptr_to_dst[index] = s[index];
		index++;
	}
	ptr_to_dst[index] = '\0';
	return (ptr_to_dst);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t  index;
	size_t  len_big_str;
	char    *sub_str;

	index = 0;
	len_big_str = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (start >= len_big_str)
		return (ft_strdup(""));
	if (len > len_big_str - start)
		len = len_big_str - start;
	sub_str = malloc(sizeof(char) * (len + 1));
	if (sub_str == NULL)
		return (NULL);
	while (index < len)
	{
		sub_str[index] = s[index + start];
		index++;
	}
	sub_str[index] = '\0';
	return (sub_str);
}
