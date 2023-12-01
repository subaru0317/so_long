/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:37:11 by smihata           #+#    #+#             */
/*   Updated: 2023/12/01 15:28:42 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (*s++ != '\0')
		len++;
	return (len);
}

char	*ft_strnjoin(char *s1, char *s2, size_t len)
{
	char	*dst;
	size_t	s1_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	dst = (char *)malloc(sizeof(char) * (s1_len + len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < s1_len && s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	i = 0;
	while (i < len && s2[i])
	{
		dst[i + s1_len] = s2[i];
		i++;
	}
	dst[i + s1_len] = '\0';
	return (dst);
}

char	*ft_strdup(const char *str)
{
	char	*cpy;
	char	*ptr;
	size_t	len;

	len = ft_strlen(str) + 1;
	cpy = (char *)malloc(sizeof(char) * len);
	if (!cpy)
		return (NULL);
	ptr = cpy;
	if (cpy == str)
		return (cpy);
	while (len--)
		*(unsigned char *)cpy++ = *(const unsigned char *)str++;
	return (ptr);
}

size_t	ft_strchr_len(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	*free_all(char **line, char **save)
{
	free(*line);
	*line = NULL;
	free(*save);
	*save = NULL;
	return (NULL);
}
